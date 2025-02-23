/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:06:08 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/23 19:38:55 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_env *env)
{
	t_env *head;

	head = env;

	while(head)
	{
		printf("%s\n", head->all);
		head = head->next;
	}
}

void	builtin_pwd(t_env *env)
{
	char *pwd;

	while(env)
	{
		// printf("\n%s\n", env->all);
		if(ft_strcmp(env->before_eq, "PWD") == 0)
		{
			pwd = env->after_eq;
			break;
		}
		env = env->next;
	}
	printf("pwd : %s\n", pwd);
}

void	builtin_echo(t_cmd *exec, int nb)
{

	t_cmd *head;

	while(exec->tkn[0] == 1)
	{
		exec = exec->next;
	}
	if(nb == 1)
	while(head != exec)
	{
		// printf("%s\n", head->arg);
		head = head->next;
	}
}
