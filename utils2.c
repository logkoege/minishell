/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:07:36 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/11 17:08:07 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_valid(char *input, t_data *data)
{
	data->single_quote = false;
	data->double_quote = false;
	if (check_pipe(input, data) == 0)
		return (0);
	if (check_other(input, data) == 0)
		return (0);
	if (check_invalid_combinations(input, data) == 0)
		return (0);
	return (1);
}

int	quote_not_closed(t_data *data)
{
	if (data->single_quote)
	{
		data->single_quote = false;
		printf("quote not closed\n");
		return (0);
	}
	if (data->double_quote)
	{
		data->double_quote = false;
		printf("doublequote not closed\n");
		return (0);
	}
	return (1);
}

int	skip_quote(char *input, t_data *data)
{
	int	i;

	i = 0;
	if (input[i] == '\'' && !data->double_quote)
	{
		data->single_quote = !data->single_quote;
		i++;
		while (input[i] && input[i] != '\'')
			i++;
	}
	else if (input[i] == '\"' && !data->single_quote)
	{
		data->double_quote = !data->double_quote;
		i++;
		while (input[i] && input[i] != '\"')
			i++;
	}
	return (i);
}

int	pipe_utils(char *input)
{
	int	i;

	i = 0;
	while (input[i] && is_ws(input[i]))
		i++;
	if (input[i] == '|')
	{
		printf("syntax pipe error\n");
		return (0);
	}
	return (1);
}
