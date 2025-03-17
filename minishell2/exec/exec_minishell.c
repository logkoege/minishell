/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:47:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/17 22:32:26 by levaipro         ###   ########.fr       */
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
		env = bultin_cd(env, cmd->arg[i]);
	}
	else if(ft_strcmp(cmd->arg[i], "pwd") == 0)
		builtin_pwd(env);
	else if(ft_strcmp(cmd->arg[i], "echo") == 0)
		builtin_echo(cmd);
	else if(ft_strcmp(cmd->arg[i], "env") == 0)
		builtin_env(env);
	else if(ft_strcmp(cmd->arg[i], "unset") == 0)
		env = builtin_unset(env, cmd->arg[1]);
	else
		return(NULL);
	return(env);

}

t_env	*exec_fils(t_data *data, t_env *env, int *fd_pipe)
{
	pid_t pid;

	(void)fd_pipe;
	char *path;
	char **env_s;


	pid = fork();
	if(pid == -1)
	{
		printf("Error : pid\n");
		exit(1);
	}
	if(pid == 0)
	{
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
		env_s = env_to_str(env);
		path = find_path(env, data->cmd->arg[0]);
		if(!path)
		{
			printf("%s : command not found\n", data->cmd->arg[0]);
			exit(1);
		}
		execve(path, data->cmd->arg, env_s);
		
	}
	else
	{
		if(data->cmd->fd_infile != STDIN_FILENO)
			close(data->cmd->fd_infile);
		if(data->cmd->fd_outfile != STDOUT_FILENO)
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
		if(data->cmd->next)
		{
			if(pipe(pipe_fd) == -1)
			{
				printf("Error : pipe\n");
				exit(1);
			}
			data->cmd->next->fd_infile = pipe_fd[0];
			data->cmd->fd_outfile = pipe_fd[1];
		}
		else
		{
			data->cmd->fd_outfile = STDOUT_FILENO;
			// data->cmd->fd_infile = STDIN_FILENO;
		}
		check_redirect(data->cmd);
		exec_fils(data, env, pipe_fd);
		data->cmd = data->cmd->next;
	}
	while(cmd_tmp)
	{
		waitpid(cmd_tmp->pid, 0, 0);
		cmd_tmp = cmd_tmp->next;
	}
	return(env);
}
