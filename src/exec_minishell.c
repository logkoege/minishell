/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:47:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/03 14:31:32 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *main_exec(t_cmd *exec, t_env *env, char **envp)
{

	env = find_env(exec, envp, env);

	// check_arg(exec, env);
	builtin_pwd(env);
	env = bultin_cd(env, "lev bg");
	builtin_pwd(env);
	// printf("her doc %s\n", first->all);
	
	return(env);
}

void check_arg(t_cmd *exec, t_env *env)
{
	int i;
	i = 0;

	if(ft_strcmp(exec->arg[i], "cd") == 0)
	{
		i++;
		env = bultin_cd(env, exec->arg[i]);
	}
	else if(ft_strcmp(exec->arg[i], "pwd") == 0)
		builtin_pwd(env);
	else if(ft_strcmp(exec->arg[i], "echo") == 0)
		builtin_echo(exec, exec->arg[i]);
}

int exec_1(t_cmd *exec, t_env *env)
{
	pid_t pid;
	int fd[2];
	int i;
	char *path;

	i = 0;
	while(exec->next)
	{
		path = find_path(env, exec->arg[i]);
		
	}
}
