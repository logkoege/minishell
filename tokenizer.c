/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:36 by logkoege          #+#    #+#             */
/*   Updated: 2025/01/27 19:13:55 by logkoege         ###   ########.fr       */
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

void	setup_tokeniser(t_data *data, char *input)
{
	char	*ssr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ssr = malloc(sizeof(char) * (ft_strlen(input) + 1));
	while (input[j] != '|' && input[j] != '>'
		&& input[j] != '<' && input[j] != ' ' && input[j])
	{
		if (input[j] == '\"')
		{
			ssr[i++] = input[j++];
			while (input[j++] != '\"')
				ssr[i++] = input[j++];
		}
		if (input[j] == '\'')
		{
			ssr[i++] = input[j++];
			while (input[j++] != '\'')
				ssr[i++] = input[j++];
		}
		ssr[i++] = input[j++];
	}
	ssr[i] = '\0';
	lstadd_back(&data->first, lstnew(tokenizer(data, ssr), ssr));
}
