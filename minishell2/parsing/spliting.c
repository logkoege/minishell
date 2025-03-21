/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:08:48 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/18 16:14:24 by logkoege         ###   ########.fr       */
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
		return (0);
	if (str == NULL)
		return (0);
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
	while (input[++i])
	{
		if (input[i] == '\'' && !data->double_quote)
			data->single_quote = !data->single_quote;
		else if (input[i] == '"' && !data->single_quote)
			data->double_quote = !data->double_quote;
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
	if (quote_not_closed(data) == 0)
	{
		free(str);
		return (NULL);
	}
	return (str);
}
