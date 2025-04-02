/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:28:12 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/01 18:41:18 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*token4(int *i, char *input, char *ssr, t_data *data)
{
	while (input[data->j] != '|' && input[data->j] != '>'
		&& input[data->j] != '<'
		&& input[data->j] != ' ' && input[data->j])
	{
		if (input[data->j] == '\"')
		{
			ssr[(*i)++] = input[data->j++];
			while (input[data->j] != '\"')
				ssr[(*i)++] = input[data->j++];
			ssr[(*i)++] = '\"';
			data->j++;
		}
		else if (input[data->j] == '\'')
		{
			ssr[(*i)++] = input[data->j++];
			while (input[data->j] != '\'')
				ssr[(*i)++] = input[data->j++];
			ssr[(*i)++] = '\'';
			data->j++;
		}
		else
			ssr[(*i)++] = input[data->j++];
	}
	return (ssr);
}

char	*token3(int *i, char *input, char *ssr, t_data *data)
{
	if (input[data->j + 1] == '<')
	{
		ssr[(*i)++] = '<';
		ssr[(*i)++] = '<';
		data->j += 2;
	}
	else
	{
		ssr[(*i)++] = '<';
		data->j++;
	}
	return (ssr);
}

char	*token2(int *i, char *input, char *ssr, t_data *data)
{
	if (input[data->j] == '|')
	{
		ssr[(*i)++] = '|';
		data->j++;
	}
	else if (input[data->j] == '>')
	{
		if (input[data->j + 1] == '>')
		{
			ssr[(*i)++] = '>';
			ssr[(*i)++] = '>';
			data->j += 2;
		}
		else
		{
			ssr[(*i)++] = '>';
			data->j++;
		}
	}
	return (ssr);
}

void	setup_tokeniser(t_data *data, char *input)
{
	char	*ssr;
	int		i;

	data->j = 0;
	while (input[data->j])
	{
		i = 0;
		ssr = malloc(sizeof(char) * (ft_strlen(input) + 1));
		if (input[data->j] == '|' || input[data->j] == '>')
			ssr = token2(&i, input, ssr, data);
		else if (input[data->j] == '<')
			ssr = token3(&i, input, ssr, data);
		else
			ssr = token4(&i, input, ssr, data);
		if (input[data->j] == ' ')
			data->j++;
		ssr[i] = '\0';
		lstadd_back(&data->first, lstnew(tokenizer(ssr), ssr));
	}
}
