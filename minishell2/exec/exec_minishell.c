/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:47:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/24 01:15:07 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *main_exec(t_data *data, t_env *env)
{
	env = exec_1(data, env);
	return(env);
}

t_env *check_arg(t_cmd *cmd, t_env *env)
{
	int i;
	i = 0;
	if(ft_strcmp(cmd->arg[0], "cd") == 0)
	{
		i++;
		if(cmd->arg[2])
		{
			write(2, "bash : cd : too many argumrents\n"
				, ft_strlen("bash : cd : too many argumrents\n"));
			// exit_code = 1;
			return(env);
		}
		env = bultin_cd(env, cmd->arg[1]);
	}
	else if(ft_strcmp(cmd->arg[0], "pwd") == 0)
		builtin_pwd(env);
	else if(ft_strcmp(cmd->arg[i], "echo") == 0)
		builtin_echo(cmd);
	else if(ft_strcmp(cmd->arg[i], "env") == 0)
		builtin_env(env);
	else if(ft_strcmp(cmd->arg[i], "unset") == 0)
		env = builtin_unset(env, cmd->arg[1]);
	else if(ft_strcmp(cmd->arg[i], "exit") == 0)
		builtin_exit(cmd);
	else if(ft_strcmp(cmd->arg[i], "export") == 0)
		env = buitlin_export(env, cmd);
	else
		return(NULL);
	return(env);

}

int is_builtin(t_data *data, t_env *env)
{
	(void)env;
	if(!data->cmd->arg[0])
		return(0);
	if(ft_strcmp(data->cmd->arg[0], "cd") == 0)
		return(1);
	if(ft_strcmp(data->cmd->arg[0], "exit") == 0)
		return(1);
	if(ft_strcmp(data->cmd->arg[0], "export") == 0)
	{
		if(data->cmd->arg[1] == NULL)
			return(0);
		return(1);
	}
	if(ft_strcmp(data->cmd->arg[0], "unset") == 0)
		return(1);
	return(0);
}

t_env	*exec_fils(t_data *data, t_env *env, int *fd_pipe)
{
	pid_t pid;
	t_env *tmp;

	(void)fd_pipe;
	char *path;
	char **env_s;
	int i;
	i = 0;

	pid = fork();
	if(pid == -1)
	{
		printf("Error : pid\n");
		// exit_code = 1;
		exit(1);
	}
	if(pid == 0)
	{
		while(data->cmd->arg[i])
		{
			if(data->cmd->arg[i][0] == '\0')
				i++;
			else
				break;
		}
		if(data->cmd->next)
		{
			dup2(data->cmd->fd_outfile, STDOUT_FILENO);
			close(data->cmd->fd_outfile);
			close(data->cmd->next->fd_infile);
		}
		if(data->cmd->prev)
		{
			dup2(data->cmd->fd_infile, STDIN_FILENO);
			close(data->cmd->fd_infile);
		}
		if(data->cmd->infile == 1)
		{
			dup2(data->cmd->fd_infile, STDIN_FILENO);
			close(data->cmd->fd_infile);
		}
		else if(data->cmd->outfile == 1)
		{
			dup2(data->cmd->fd_outfile, STDOUT_FILENO);
			close(data->cmd->fd_outfile);
		}
		tmp = check_arg(data->cmd, env);
		if(tmp)
		{
			close(data->cmd->fd_infile);
			close(data->cmd->fd_outfile);
			exit(0);
		}
		env_s = env_to_str(env);
		// if(!data->cmd->arg[i])
		// 	i++;
		path = find_path(env, data->cmd->arg[i]);
		if(!path)
		{
			printf("%s : command not found\n", data->cmd->arg[i]);
			free_path(env, env_s);
			// free(path);
			// exit_code = 127;
			exit(127);
		}
		if(execve(path, data->cmd->arg, env_s) == 1)
		{
			if(path)
				free(path);
			free_path(env, env_s);
			printf("execve error \n");
			// exit_code = 1;
			exit(1);
		}
	}
	else
	{
		if(data->cmd->fd_infile != STDIN_FILENO && data->cmd->fd_infile != -4242)
			close(data->cmd->fd_infile);
		if(data->cmd->fd_outfile != STDOUT_FILENO && data->cmd->fd_outfile != -4242)
			close(data->cmd->fd_outfile);
		data->cmd->pid = pid;
		// close(data->cmd->fd_infile);
		// close(data->cmd->fd_outfile);
	}
	return(env);
}

t_env	*exec_1(t_data *data, t_env *env)
{
	int pipe_fd[2];
	t_cmd *cmd_tmp;

	cmd_tmp = data->cmd;
	while(data->cmd)
	{

		if(!data->cmd->next && !data->cmd->prev)
		{
			// printf("YES\n");
			if(is_builtin(data, env))
			{
				check_redirect(data->cmd);
				if(data->cmd->infile == 1)
				{
					dup2(data->cmd->fd_infile, STDIN_FILENO);
					close(data->cmd->fd_infile);
				}
				else if(data->cmd->outfile == 1)
				{
					dup2(data->cmd->fd_outfile, STDOUT_FILENO);
					close(data->cmd->fd_outfile);
				}
				env = check_arg(data->cmd, env);
				return(env);
			}
		}
		if(check_redirect(data->cmd) == 1)
		{
			if(data->cmd->next)
			{
				if(pipe(pipe_fd) == -1)
				{
					printf("Error : pipe\n");
					exit(1);
				}
				data->cmd->next->fd_infile = pipe_fd[0];
				data->cmd->fd_outfile = pipe_fd[1];
				close(pipe_fd[1]);
			}
			data->cmd = data->cmd->next;
			continue;
		}		
		if(data->cmd->next)
		{
			if(pipe(pipe_fd) == -1)
			{
				printf("Error : pipe\n");
				exit(1);
			}
			data->cmd->next->fd_infile = pipe_fd[0];
			if(data->cmd->outfile == 1)
				close(pipe_fd[1]);
			else
				data->cmd->fd_outfile = pipe_fd[1];
		}
		else
		{
			if(data->cmd->outfile != 1)
				data->cmd->fd_outfile = STDOUT_FILENO;
			if(data->cmd->infile != 1 && !data->cmd->prev)
				data->cmd->fd_infile = STDIN_FILENO;
		}
		env = exec_fils(data, env, pipe_fd);
		data->cmd = data->cmd->next;
	}
	int status;
	while(cmd_tmp)
	{
		if(cmd_tmp->pid)
			waitpid(cmd_tmp->pid, NULL, 0);
		if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
		cmd_tmp = cmd_tmp->next;
	}

	return(env);
}
