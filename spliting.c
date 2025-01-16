/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:08:48 by logkoege          #+#    #+#             */
/*   Updated: 2025/01/16 16:39:26 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*start_split(t_data *data, char *input)
{
	char	*str;

	if (token_is_valid(input) == 0)
	{
		return (NULL);
	}
	str = delete_space(data, input);
	printf("str = %s\n", str);
	return (str);
}

char	*delete_space(t_data *data, char *input)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	str = (char *)malloc(sizeof(char) * (inputlen(input) + 1));
	if (!str)
		return (NULL);
	while (input[++i])
	{
		if (input[i] == '\'' && !data->double_quote)
			data->single_quote = !data->single_quote;
		else if (input[i] == '"' && !data->single_quote)
			data->double_quote = !data->double_quote;
		if (input[i] != ' ' || data->single_quote
			|| data->double_quote || (j > 0 && str[j - 1] != ' '))
			str[j++] = input[i];
	}
	if (j > 0 && str[j - 1] == ' '
		&& !data->single_quote && !data->double_quote)
		str[j - 1] = '\0';
	else
		str[j] = '\0';
	return (str);
}
