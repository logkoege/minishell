/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:10:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/10 16:45:05 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_parser(t_data *data, char **envp)
{
	(void)envp;
	while (data->first->next != NULL)
	{
		dollar_checker(data, envp);
		data->first = data->first->next;
	}
	dollar_checker(data, envp);
}

void	dollar_checker(t_data *data, char **envp)
{
	int	i;

	i = 0;
	(void)envp;
	while (data->first->str[i])
	{
		if (data->first->str[i] == '\"')
		{
			i++;
			while (data->first->str[i] != '\"')
			{
				if (data->first->str[i] == '$')
					dollar_changer(data, i);
				i++;
			}
			i++;
		}
		if (data->first->str[i] == '\'')
		{
			i++;
			while (data->first->str[i] != '\'')
				i++;
			i++;
		}
		i++;
	}
}

void	dollar_changer(t_data *data, int i)
{
	i++;
	while ((data->first->str[i] && data->first->str[i] >= 'A'
			&& data->first->str[i] >= 'Z') || (data->first->str[i] == '_'))
	{
		//if (strcmp a partir de $ justqua la fin de la partie de la string == 0)
		//	changement de la sting avec le $ en la nouvelle valeur de env
			i++;
	}
}
