/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:36 by logkoege          #+#    #+#             */
/*   Updated: 2025/01/20 14:23:57 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer_utils(t_data *data, char *str, char n)
{
	if (str[data->i] == n)
	{
		if (str[data->i + 1] == n)
		{
			data->i += 2;
			return (2);
		}
		data->i++;
		return (1);
	}
	return (0);
}

int	tokenizer(t_data *data, char *str)
{
	while (is_ws(str[data->i]))
		data->i++;
	if (str[data->i] == '|')
	{
		data->i++;
		return (2);
	}
	if (tokenizer_utils(data, str, '>') == 2)
		return (5);
	if (tokenizer_utils(data, str, '<') == 2)
		return (6);
	if (tokenizer_utils(data, str, '>') == 1)
		return (3);
	if (tokenizer_utils(data, str, '<') == 1)
		return (4);
	return (1);
}
