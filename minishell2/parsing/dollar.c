/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:10:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/07 16:49:53 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dollar_parser(t_data *data, t_env *env)
{
	t_first	*tmp;

	tmp = data->first;
	while (tmp)
	{
		dollar_checker(tmp, env);
		tmp = tmp->next;
	}
}

void	dollar_checker(t_first *tmp, t_env *env)
{
	int	i;

	i = 0;
	while (tmp->str[i])
	{
		if (tmp->str[i] == '\'')
		{
			i++;
			while (tmp->str[i] != '\'')
				i++;
			i++;
		}
		if (tmp->str[i] == '\"')
		{
			i++;
			while (tmp->str[i] != '\"')
			{
				if (tmp->str[i] == '$')
				{
					dollar_changer(tmp, i, env, true);
				}
				i++;
			}
			i++;
		}
		else if (tmp->str[i] != '\'' && tmp->str[i] != '\0')
		{
			while (tmp->str[i] != '\0')
			{
				if (tmp->str[i] == '$')
					dollar_changer(tmp, i, env, false);
				i++;
			}
		}
		i++;
	}
}

void	dollar_changer(t_first *tmp, int i, t_env *env, bool quote)
{
	t_env	*tenv2;
	char	*str;

	i++;
	tenv2 = dollar_cmp(tmp, env, i, quote);
	if (tenv2 != NULL)
	{
		str = malloc(sizeof(char) * (ft_strlen(tmp->str)
					+ ft_strlen(tenv2->after_eq)));
		//printf("tenv2 = %s\n", tenv2->after_eq);
		replace_dollar(tmp, tenv2, str, i);
	}
}

t_env	*dollar_cmp(t_first *tmp, t_env *env, int i, bool quote)
{
	t_env	*tenv;
	int		j;
	int		t;

	j = 0;
	t = i;
	tenv = env;
	while (tenv)
	{
		j = 0;
		i = t;
		while (tenv->before_eq[j] == tmp->str[i] || tenv->before_eq[j] == '\0')
		{
			//printf("tenv->before_eq[j] = %c\n", tenv->before_eq[j]);
			//printf("tmp->str[i] = %c\n", tmp->str[i]);
			if (tenv->before_eq[j] == '\0')
			{
				if (quote == true && tmp->str[i] == '\"')
					return (tenv);
				else if ((tmp->str[i] == '\0' || tmp->str[i] == ' '))
					return (tenv);
				else
					break ;
			}
			i++;
			j++;
		}
		tenv = tenv->next;
	}
	return (NULL);
}

void	replace_dollar(t_first *tmp, t_env *tenv2, char *str, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < i - 1)
	{
		str[j] = tmp->str[j];
		j++;
	}
	while (tenv2->after_eq[k])
	{
		str[j] = tenv2->after_eq[k];
		j++;
		k++;
	}
	i = i + ft_strlen(tenv2->before_eq);
	while (tmp->str[i])
	{
		str[j] = tmp->str[i];
		i++;
		j++;
	}
	free(tmp->str);
	tmp->str = str;
	//printf("str = %s\n", str);
}
