/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:47:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/10 17:39:07 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *main_exec(t_data *data, t_env *env)
{

	// env = find_env(exec, envp, env);
	env = exec_1(data, env);
	// check_arg(data, env);
	// check_arg(exec, env);
	// builtin_pwd(env);
	// (void)exec;
	// env = bultin_cd(env, exec->arg[1]);
	// builtin_pwd(env);
	// printf("her doc %s\n", first->all);
	
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

t_env *exec_1(t_data *data, t_env *env)
{
	// t_env *tmp;
	pid_t pid;
	// int fd[2];
	int i;
	(void)i;

	i = 0;
	// env = check_arg(data->cmd, env);
	while(data->cmd)
	{
		
		pid = fork();
		pipe(data->pipe);
		if(pid == 0)
		{
			env = exec_fils(data, env);
		}
		else
		{
			waitpid(pid, NULL, 0);
			if(data->cmd->next)
			{
				dup2(data->pipe[0], 0);
				close(data->pipe[1]);
			}
		}
		data->cmd = data->cmd->next;
	}
	return(env);
}

t_env	*exec_fils(t_data *data, t_env *env)
{
	char *path;
	t_env *tmp;

	if(data->cmd->next)
	{
		dup2(data->pipe[1], 1);
		close(data->pipe[0]);
	}
	tmp = check_arg(data->cmd, env);
	if(tmp)
		return(tmp);
	path = find_path(env, data->cmd->arg[0]);
	if(!path)
		ft_fprintf("command not found\n");
	execve(path, data->cmd->arg, NULL);
	free(path);
	return(env);
}
