/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:08:48 by logkoege          #+#    #+#             */
/*   Updated: 2025/01/16 15:12:00 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*start_split(t_data *data, char *input)
{
	char	*str;

	token_is_valid(input);
	str = delete_space(data, input);
	return (str);
}

char	*delete_space(t_data *data, char *input)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (inputlen(input) + 1));
	if (!str)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' && !data->double_quote)
			data->single_quote = !data->single_quote;
		else if (input[i] == '"' && !data->single_quote)
			data->double_quote = !data->double_quote;
		if (input[i] != ' ' || data->single_quote
			|| data->double_quote || (j > 0 && str[j - 1] != ' '))
			str[j++] = input[i];
		i++;
	}
	if (j > 0 && str[j - 1] == ' '
		&& !data->single_quote && !data->double_quote)
		str[j - 1] = '\0';
	else
		str[j] = '\0';
	printf("str = %s\n", str);
	return (str);
}

char	*add_space(char *input)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	str = malloc(sizeof(char) * (inputlen(input) + 1));
	while (input[i])
	{
		if (input[i] == '\"')
		{
			str[j++] = input[i++];
			while (input[i] && input[i] != '\"')
				str[j++] = input[i++];
		}
		if (input[i] == '\'')
		{
			str[j++] = input[i++];
			while (input[i] && input[i] != '\'')
				str[j++] = input[i++];
		}
		if (token_is_valid(&input[i]))
		{
			str[j++] = ' ';
			str[j++] = input[i++];
			str[j++] = ' ';
		}
		else
			str[j++] = input[i++];
		i++;
	}
	return (str);
}
