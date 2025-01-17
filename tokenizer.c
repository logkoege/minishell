/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:36 by logkoege          #+#    #+#             */
/*   Updated: 2025/01/17 18:41:11 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer_utils(t_data *data,char *str, char n)
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

int	tokenizer(t_data *data,char *str)
{
	while (is_ws(str[data->i]))
		data->i++;
	if (str[data->i] == '|')
	{
		data->i++;
		return (2);
	}
	if (tokenizer_utils(data, str, '>') == 1)
		return (3);
	if (tokenizer_utils(data, str, '<') == 1)
		return (4);
	if (tokenizer_utils(data, str, '>') == 2)
		return (5);
	if (tokenizer_utils(data, str, '<') == 2)
		return (6);
	return (1);
}
int	is_ws(char c)
{
	if ((c == ' ' ) || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int main(void)
{
	t_data data;
	char *str = " | >> > << <";
	data.i = 0;
	while(is_ws(str[data.i]))
		printf("%d\n", tokenizer(&data, str));
	return (0);
}
