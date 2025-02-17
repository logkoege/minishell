/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:47:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/17 14:32:33 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	main_exec(t_cmd *exec, t_env *env, char **envp)
{
	check_arg(exec, env);
	env = find_env(exec, envp, env);
	builtin_export(exec, env);
	// exec_1(exec, env);


}
void	check_arg(t_cmd *exec, t_env *env)
{
	int i;

	i = 0;

	// bultin_cd(env, "src");
	// if(ft_strcmp(exec->arg, "cd") == 0)
	// 	bultin_cd(env, exec->next->arg);
	// else if(ft_strcmp(exec->arg, "pwd") == 0)
	// 	builtin_pwd(env);
	// else if(ft_strcmp(exec->arg, "echo") == 0)
	// {
	// 	if(ft_strcmp(exec->next->arg, "-n") == 0)
	// 		i = 1;
	// 	builtin_echo(exec, i);
	// }
	// else if(ft_strcmp(exec->arg, "env") == 0)
	// 	builtin_env(env);
}

int exec_1(t_cmd *exec, t_env *env)
{
	
	find_path(env, "ls");
	// while(exec->tkn)
	// {
	
	// }
	return(0);
}