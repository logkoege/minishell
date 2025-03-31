/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:12:18 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/28 12:20:27 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*is_first(t_env *env, t_env *head)
{
	if(env->all)
		free(env->all);
	if(env->before_eq)
		free(env->before_eq);
	if(env->after_eq)
		free(env->after_eq);
	env->all = NULL;
	env->equal = 0;
	env->before_eq = NULL;
	env->after_eq = NULL;
	head = env->next;
	free(env);
	return(head);
}
t_env *main_unset(t_env *env, char *unset, t_env *head, t_env *tmp)
{
	env = env->next;
	while(env)
	{
		if(ft_strcmp(env->before_eq, unset) == 0)
		{
			if(env->all)
				free(env->all);
			if(env->before_eq)
				free(env->before_eq);
			if(env->after_eq)
				free(env->after_eq);
			env->all = NULL;
			env->before_eq = NULL;
			env->equal = 0;
			env->after_eq = NULL;
			head->next = env->next;
			free(env);
			break;
		}
		env = env->next;
		head = head->next;
	}
	head = tmp;
	return(tmp);
}


t_env *builtin_unset(t_env *env, char *unset)
{
	t_env *tmp;
	t_env *head;

	tmp = env;
	head = env;
	if(!unset)
		return(tmp);
	if(ft_strcmp(env->before_eq, unset) == 0)
		return(is_first(env, head));
	else
		return(main_unset(env, unset, head, tmp));
	
}
