/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:31:12 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/31 17:05:13 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// 
void	handle_operator(char *input, t_data *data, char *ssr, int *i)
{
	if (input[data->j] == '|')
	{
		ssr[(*i)++] = '|';
		data->j++;
	}
	else if (input[data->j] == '>')
	{
		ssr[(*i)++] = '>';
		if (input[data->j + 1] && input[data->j + 1] == '>')
		{
			ssr[(*i)++] = '>';
			data->j++;
		}
		data->j++;
	}
	else if (input[data->j] == '<')
	{
		ssr[(*i)++] = '<';
		if (input[data->j + 1] && input[data->j + 1] == '<')
		{
			ssr[(*i)++] = '<';
			data->j++;
		}
		data->j++;
	}
}

void	handle_quotes(char *input, t_data *data, char *ssr, int *i)
{
	char	quote;

	quote = input[data->j];
	ssr[(*i)++] = input[data->j++];
	while (input[data->j] && input[data->j] != quote)
		ssr[(*i)++] = input[data->j++];
	if (input[data->j] == quote)
		ssr[(*i)++] = input[data->j++];
}

void	handle_word(char *input, t_data *data, char *ssr, int *i)
{
	while (input[data->j] && input[data->j] != '|' && input[data->j] != '>'
		&& input[data->j] != '<' && input[data->j] != ' ')
	{
		if (input[data->j] == '"' || input[data->j] == '\'')
			handle_quotes(input, data, ssr, i);
		else
			ssr[(*i)++] = input[data->j++];
	}
}

void	setup_tokeniser(t_data *data, char *input)
{
	char	*ssr;
	int		i;

	data->j = 0;
	while (input[data->j])
	{
		i = 0;
		ssr = malloc(sizeof(char) * (ft_strlen(input) - data->j + 1));
		if (!ssr)
			return ;
		if (input[data->j] == '|' || input[data->j] == '>'
			|| input[data->j] == '<')
			handle_operator(input, data, ssr, &i);
		else
			handle_word(input, data, ssr, &i);
		if (input[data->j] == ' ')
			data->j++;
		ssr[i] = '\0';
		if (i > 0)
			lstadd_back(&data->first, lstnew(tokenizer(ssr), ssr));
		else
			free(ssr);
	}
}
