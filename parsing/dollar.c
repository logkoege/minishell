/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:10:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/03 18:37:55 by lloginov         ###   ########.fr       */
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

int	dollar_changer(t_first *tmp, int i, t_env *env)
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
		str = malloc(sizeof(char) * (ft_strlen(tmp->str) + 6));
		if (remove_dollar(tmp, str, i) == 1)
			return (1);
	}
	return (0);
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
		str[j++] = tmp->str[i++];
	str[j] = '\0';
	free(tmp->str);
	tmp->str = str;
}
