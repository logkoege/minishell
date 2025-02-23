/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:47:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/23 20:43:47 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void main_exec(t_cmd *exec, t_env *env, char **envp)
{

	env = find_env(exec, envp, env);

	// check_arg(exec, env);
	env = bultin_cd(env, NULL);
	env = bultin_cd(env, "-");
	// printf("her doc %s\n", first->all);
	builtin_pwd(env);
	
}
// void check_arg(t_cmd *exec, t_env *env)
// {
// 	int i;

// 	i = 0;

// 	if(ft_strcmp(exec->arg, "cd") == 0)
// 		bultin_cd(env, exec->next->arg);
// 	else if(ft_strcmp(exec->arg, "pwd") == 0)
// 		builtin_pwd(env);
// 	else if(ft_strcmp(exec->arg, "echo") == 0)
// 	{
// 		if(ft_strcmp(exec->next->arg, "-n") == 0)
// 			i = 1;
// 		builtin_echo(exec, i);
// 	}
// 	else if(ft_strcmp(exec->arg, "env") == 0)
// 		builtin_env(env);
// }

int exec_1(t_cmd *exec, t_env *env)
{
	(void)exec;
	(void)env;
	// int i;

	// i = 0;
	// char *path;
	// if(!exec | !env)
	// 	return(NULL);
	// while(exec != NULL)
	// {
	// 	if(exec->tkn == 1 && exec->next->tkn != 2)
	// 	{
	// 		if(!(path = find_path(env, exec->arg[i])))
	// 			return(1);
	// 		execve(path, exec->arg[i],env);

	// 	}
	// }
	return (0);
}