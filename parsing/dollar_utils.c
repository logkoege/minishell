/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:38:38 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/08 14:48:53 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sob_utils(t_data *data, t_first *tmp, t_env *env)
{
	if (tmp->str[data->sob] == '\'' && tmp->str[data->sob + 1] != '\0')
	{
		data->sob++;
		while (tmp->str[data->sob] && tmp->str[data->sob] != '\'')
			data->sob++;
		data->sob++;
	}
	else if (tmp->str[data->sob] == '\"')
	{
		data->sob++;
		while (tmp->str[data->sob] != '\"' && tmp->str[data->sob] != '\0')
		{
			if (tmp->str[data->sob] == '$')
			{
				data->quote = true;
				if (dollar_changer(tmp, data->sob, env) == 0)
				{
					data->sob = 0;
					return ;
				}
			}
			data->sob++;
		}
		data->sob++;
	}
}

void	dollar_checker(t_first *tmp, t_env *env, t_data *data)
{
	data->sob = 0;
	while (tmp->str[data->sob])
	{
		if ((tmp->str[data->sob] == '\'' && tmp->str[data->sob + 1] != '\0')
			|| tmp->str[data->sob] == '\"')
			sob_utils(data, tmp, env);
		else if (tmp->str[data->sob] != '\'' && tmp->str[data->sob] != '\0')
		{
			while (tmp->str[data->sob] != '\0')
			{
				if (tmp->str[data->sob] == '$')
				{
					data->quote = false;
					if (dollar_changer(tmp, data->sob, env) == 0)
					{
						data->sob = 0;
						break ;
					}
				}
				data->sob++;
			}
		}
	}
}

int	dollar_utils(t_env *tenv, t_first *tmp, int i, int j)
{
	while (tenv->before_eq[j] == tmp->str[i] || tenv->before_eq[j] == '\0')
	{
		if (tenv->before_eq[j] == '\0')
		{
			if (((tmp->str[i] == '\0' || tmp->str[i] == '$'
						|| tmp->str[i] == ' ') || tmp->str[i] == '\"')
				|| (!is_alpha(tmp->str[i]) && !is_digit(tmp->str[i])))
				return (1);
			else
				return (0);
		}
		i++;
		j++;
	}
	return (0);
}

t_env	*dollar_cmp(t_first *tmp, t_env *env, int i)
{
	t_env	*tenv;
	int		j;

	j = 0;
	tenv = env;
	while (tenv)
	{
		j = 0;
		if (dollar_utils(tenv, tmp, i, j) == 1)
			return (tenv);
		tenv = tenv->next;
	}
	return (NULL);
}
