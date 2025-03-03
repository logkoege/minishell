/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:06:08 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/25 17:01:53 by lloginov         ###   ########.fr       */
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
	if (pwd != NULL)
		printf("pwd : %s\n", pwd);
	else
		printf("Error : nopwd\n");
}

void	builtin_echo(t_cmd *exec, int nb)
{

	t_cmd *head;
	int i;
	int comt;

	comt = 0;
	i = 0;
	if(ft_strcmp(exec->arg[1], "-n") == 0)
		comt = 1;
	while(exec->tkn[i] == 1)
	{
		printf("%s", exec->arg[i]);
		i++;
	}
	if(comt != 1)
		printf("\n");
}
