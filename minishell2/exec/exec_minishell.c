/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:47:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/17 16:37:04 by lloginov         ###   ########.fr       */
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
t_env	*exec_alone(t_data *data,t_env *env)
{
	t_env *tmp;
	char *path;

	tmp = check_arg(data->cmd, env);
	if(tmp)
		return(tmp);
	path = find_path(env, data->cmd->arg[0]);
	if(!path)
	{
		ft_fprintf("command not found \n");
		exit(127);
	}
	if(execve(path, data->cmd->arg, NULL) == -1)
	{
		ft_fprintf("execve\n");
		free(path);
		exit(EXIT_FAILURE);
	}
	return(env);
}
t_env	*exec_first(t_data *data, t_env *env)
{
	t_env *tmp;

	tmp = check_arg(data->cmd, env);
	if(tmp)
		return(tmp);
	// check_redirect(data->cmd);
	// dup2(data->cmd->fd_infile, STDIN_FILENO);
	// if(data->cmd->fd_infile != 0)
	// 	close(data->cmd->fd_infile);
	dup2(data->pipe[0], STDOUT_FILENO);
	close(data->pipe[1]);
	exec_alone(data, env);
	return(env);

}


t_env *exec_1(t_data *data, t_env *env)
{
	pid_t pid;

	pid = fork();
	if(pid == -1)
	{
		printf("Erorr : pid exec\n");
		return(env);
	}
	if(pid == 0  && data->cmd->next != NULL)
	{
		printf("yes\n");
		env = exec_first(data, env);
		return(env);
	}
	pipe(data->pipe);
	while(data->cmd)
	{
		if(pid == 0)
		{
			env = exec_fils(data, env);
			// exit(0);
		}
		else
		{
			waitpid(pid, 0, 0);

		}
		data->cmd = data->cmd->next;
	}
	close(data->pipe[0]);
	close(data->pipe[1]);
	return(env);
}

t_env	*exec_fils(t_data *data, t_env *env)
{
	t_env *tmp;

	check_redirect(data->cmd);
	dup2(data->cmd->fd_infile, STDIN_FILENO);
	if(data->cmd->fd_infile != 0)
		close(data->cmd->fd_infile);
	if(data->cmd->next)
	{
		dup2(data->pipe[1], STDOUT_FILENO);
		close(data->pipe[0]);
		close(data->pipe[1]);
	}
	else
	{
		dup2(data->cmd->fd_outfile, STDOUT_FILENO);
		if(data->cmd->fd_outfile != 1)
			close(data->cmd->fd_outfile);
	}
	tmp = exec_alone(data, env);
	if(tmp != NULL)
		return(tmp);
	return(env);
}

