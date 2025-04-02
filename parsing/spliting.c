/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:08:48 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/01 18:49:11 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start_split(t_data *data, char *input)
{
	char	*str;

	data->single_quote = false;
	data->double_quote = false;
	str = delete_space(data, input, 0);
	if (token_is_valid(input, data) == 0)
	{
		free(str);
		return (0);
	}
	if (str == NULL)
	{
		free(str);
		return (0);
	}
	setup_tokeniser(data, str);
	free(str);
	return (1);
}

char	*delete_space(t_data *data, char *input, int j)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)malloc(sizeof(char) * (inputlen(input) + 1));
	if (!str)
		return (NULL);
	while (input[++i])
	{
		in_delete_space(i, input, data);
		if (input[i] >= 9 && input[i] <= 13
			&& !data->single_quote && !data->double_quote)
			input[i] = ' ';
		if (input[i] != ' ' || data->single_quote
			|| data->double_quote || (j > 0 && str[j - 1] != ' '))
			str[j++] = input[i];
	}
	if (j > 0 && str[j - 1] == ' '
		&& !data->single_quote && !data->double_quote)
		str[j - 1] = '\0';
	str[j] = '\0';
	if (quote_not_closed(data, str) == 0)
		return (NULL);
	return (str);
}

void	in_delete_space(int i, char *input, t_data *data)
{
	if (input[i] == '\'' && !data->double_quote)
		data->single_quote = !data->single_quote;
	else if (input[i] == '"' && !data->single_quote)
		data->double_quote = !data->double_quote;
}
