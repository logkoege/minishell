/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:10:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/10 17:42:38 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_parser(t_data *data)
{
	t_first	*tmp;

	tmp = data->first;
	while (tmp->next != NULL)
	{
		dollar_checker(tmp);
		tmp = tmp->next;
	}
	dollar_checker(tmp);
}

void	dollar_checker(t_first *tmp)
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
					dollar_changer(tmp, i);
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

void	dollar_changer(t_first *tmp, int i)
{
	i++;
	while ((tmp->str[i] && tmp->str[i] >= 'A'
			&& tmp->str[i] >= 'Z') || (tmp->str[i] == '_'))
	{
		//if (strcmp a partir de $ justqua la fin de la partie de la string == 0)
		//	changement de la sting avec le $ en la nouvelle valeur de env
			i++;
	}
}
