/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:47:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/07 17:57:45 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *main_exec(t_cmd *exec, t_env *env)
{

	// env = find_env(exec, envp, env);

	check_arg(exec, env);
	// check_arg(exec, env);
	// builtin_pwd(env);
	// (void)exec;
	// env = bultin_cd(env, exec->arg[1]);
	// builtin_pwd(env);
	// printf("her doc %s\n", first->all);
	
	return(env);
}

void check_arg(t_cmd *exec, t_env *env)
{
	int i;
	i = 0;

	printf("nononon%s\n", exec->arg[0]);
	if(ft_strcmp(exec->arg[0], "cd") == 0)
	{
		i++;
		env = bultin_cd(env, exec->arg[i]);
	}
	else if(ft_strcmp(exec->arg[i], "pwd") == 0)
		builtin_pwd(env);
	else if(ft_strcmp(exec->arg[i], "echo") == 0)
		builtin_echo(exec, 1);
	else
		return;
}

int exec_1(t_cmd *exec, t_env *env)
{
	(void)exec;
	(void)env;
	return(0);
	// pid_t pid;
	// int fd[2];
	// int i;
	// char *path;

	// i = 0;
	// while(exec->next)
	// {
	// 	path = find_path(env, exec->arg[i]);
		
	// }
}
