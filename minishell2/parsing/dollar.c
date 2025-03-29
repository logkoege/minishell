/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:10:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/29 18:56:49 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dollar_parser(t_data *data, t_env *env)
{
	t_first	*tmp;

	tmp = data->first;
	while (tmp)
	{
		dollar_checker(tmp, env, data);
		tmp = tmp->next;
	}
}

void	dollar_checker(t_first *tmp, t_env *env, t_data *data)
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
					data->quote = true;
					if (dollar_changer(tmp, i, env, data) == 0)
						i = -1;
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
				{
					data->quote = false;
					if (dollar_changer(tmp, i, env, data) == 0)
						i = -1;
				}
				i++;
			}
		}
		if (tmp->str[i] == '\0')
			break ;
		i++;
	}
}

int	dollar_changer(t_first *tmp, int i, t_env *env, t_data *data)
{
	t_env	*tenv2;
	char	*str;

	i++;
	tenv2 = dollar_cmp(tmp, env, i);
	if (tenv2 != NULL)
	{
		str = malloc(sizeof(char) * (ft_strlen(tmp->str)
					+ ft_strlen(tenv2->after_eq) + 2));
		replace_dollar(tmp, tenv2, str, i);
	}
	else if (tenv2 == NULL)
	{
		str = malloc(sizeof(char) * (ft_strlen(tmp->str) + 2));
		if (remove_dollar(tmp, str, i, data) == 1)
			return (1);
	}
	return (0);
}

t_env	*dollar_cmp(t_first *tmp, t_env *env, int i)
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
			if (tenv->before_eq[j] == '\0')
			{
				if (!is_digit(tmp->str[i]))
					return (tenv);
				break ;
			}
			i++;
			j++;
		}
		if (tenv->before_eq[j] == '\0' && tmp->str[i] == '$')
			return (tenv);
		tenv = tenv->next;
	}
	return (NULL);
}

void	replace_dollar(t_first *tmp, t_env *tenv2, char *str, int i)
{
	int		j;
	int		k;

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
		str[j++] = tmp->str[i++];
	}
	str[j] = '\0';
	free(tmp->str);
	tmp->str = str;
}
