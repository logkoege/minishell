/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:12:18 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/10 17:37:28 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	builtin_exit(t_cmd *cmd)
{
	(void)cmd;
	// printf("%s\n", cmd->arg);
	exit(0);
}

t_env *builtin_unset(t_env *env, char *unset)
{
	t_env *tmp;
	t_env *head;

	tmp = env;
	head = env;
	if(ft_strcmp(env->before_eq, unset) == 0)
	{
		// env = env->next;
		free(env->all);
		env->all = NULL;
		env->before_eq = NULL;
		env->after_eq = NULL;
		// env = head;
		env = env->next;
		return(env);
	}
	else
	{
		env = env->next;
		while(env)
		{
			if(ft_strcmp(env->before_eq, unset) == 0)
			{
				free(env->all);
				env->all = NULL;
				env->before_eq = NULL;
				env->after_eq = NULL;
				head->next = env->next;
			}
			env = env->next;
			head = head->next;
		}
	}
	head = tmp;
	return(tmp);
}
