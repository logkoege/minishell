/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:10:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/11 17:07:00 by logkoege         ###   ########.fr       */
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

	i++;
	t = i;
	while ((tmp->next != NULL))
	{
		if (dollar_cmp(tmp, env, i) == 1);
			change_it
	}
	//refaire une fois la boucle
}

int	dollar_cmp(t_first *tmp, t_env *env, int i)
{
	t_env	*tenv;
	int		j;


	j = 0;
	tenv = env;
	while (tenv->before_eq[i] == )
}
