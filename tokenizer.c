/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:36 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/03 16:50:32 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer_utils(char *str, char n)
{
	int i;

	i = 0;
	if (str[i] == n)
	{
		if (str[i + 1] == n)
		{
			i += 2;
			return (2);
		}
		i++;
		return (1);
	}
	return (0);
}

int	tokenizer(char *str)
{
	int i;

	i = 0;
	if (str[i] == '|')
	{
		return (2);
	}
	if (tokenizer_utils(str, '>') == 2)
		return (5);
	if (tokenizer_utils(str, '<') == 2)
		return (6);
	if (tokenizer_utils(str, '>') == 1)
		return (3);
	if (tokenizer_utils(str, '<') == 1)
		return (4);
	return (1);
}

void	setup_tokeniser(t_data *data, char *input)
{
	char	*ssr;
	int		i;

	i = 0;
	while (input[data->j])
	{
		i = 0;
		ssr = malloc(sizeof(char) * (ft_strlen(input) + 1));
		if (input[data->j] == '|')
		{
			ssr[i++] = '|';
			data->j++;
		}
		else if (input[data->j] == '>')
		{
			if (input[data->j + 1] == '>')
			{
				ssr[i++] = '>';
				ssr[i++] = '>';
				data->j += 2;
			}
			else
			{
				ssr[i++] = '>';
				data->j++;
			}
		}
		else if (input[data->j] == '<')
		{
			if (input[data->j + 1] == '<')
			{
				ssr[i++] = '<';
				ssr[i++] = '<';
				data->j += 2;
			}
			else
			{
				ssr[i++] = '<';
				data->j++;
			}
		}
		else
		{
			while (input[data->j] != '|' && input[data->j] != '>'
				&& input[data->j] != '<' && input[data->j] != ' ' && input[data->j])
			{
				if (input[data->j] == '\"')
				{
					ssr[i++] = input[data->j++];
					while (input[data->j] != '\"')
						ssr[i++] = input[data->j++];
					ssr[i++] = '\"';
					data->j++;
				}
				else if (input[data->j] == '\'')
				{
					ssr[i++] = input[data->j++];
					while (input[data->j] != '\'')
						ssr[i++] = input[data->j++];
					ssr[i++] = '\'';
					data->j++;
				}
				else
					ssr[i++] = input[data->j++];
			}
		}
		if (input[data->j] == ' ')
			data->j++;
		ssr[i] = '\0';
		lstadd_back(&data->first, lstnew(tokenizer(ssr), ssr));
		free(ssr);
	}
}
