/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:10:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/11 17:51:31 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_parser(t_data *data, t_env *env)
{
	t_first	*tmp;

	tmp = data->first;
	while (tmp->next != NULL)
	{
		dollar_checker(tmp, env);
		tmp = tmp->next;
	}
	dollar_checker(tmp, env);
}

void	dollar_checker(t_first *tmp, t_env *env)
{
	int	i;

	i = 0;
	while (tmp->str[i])
	{
		if (tmp->str[i] == '\"')
		{
			i++;
			while (tmp->str[i] != '\"')
			{
				if (tmp->str[i] == '$')
					dollar_changer(tmp, i, env);
				i++;
			}
			i++;
		}
		if (tmp->str[i] == '\'')
		{
			i++;
			while (tmp->str[i] != '\'')
				i++;
			i++;
		}
		i++;
	}
}

void	dollar_changer(t_first *tmp, int i, t_env *env)
{
	int	t;
	t_env	*tenv2;

	i++;
	tenv2 = dollar_cmp(tmp, env, i);
		printf("tenv = %s\n", tenv2->before_eq);
	
}

t_env	*dollar_cmp(t_first *tmp, t_env *env, int i)
{
	t_env	*tenv;
	int		j;
	int		t;

	j = 0;
	t = i;
	tenv = env;
	while (tenv->next != NULL)
	{
		j = 0;
		i = t;
		while (tenv->before_eq[j] == tmp->str[i])
		{
			i++;
			j++;
			if (tenv->before_eq[j] == '\0' && tmp->str[i] == '\0'
				|| tmp->str[i] == ' ' || tmp->str[i] == '\"')
				return (tenv);
		}
		env = tenv->next;
	}
	j = 0;
	i = t;
	while (tenv->before_eq[j] == tmp->str[i])
	{
		i++;
		j++;
		if (tenv->before_eq[j] == '\0' && tmp->str[i] == '\0'
			|| tmp->str[i] == ' ' || tmp->str[i] == '\"')
			return (tenv);
	}
	return (NULL);
}

void	change_it()