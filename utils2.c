/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:07:36 by logkoege          #+#    #+#             */
/*   Updated: 2025/01/16 16:56:22 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_valid(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (check_pipe(&input[i]) == 0)
			return (0);
		if (check_other(&input[i]) == 0)
			return (0);
		if (check_invalid_combinations(&input[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
int quote_not_closed(t_data *data)
{
	if (data->single_quote)
	{
		printf("quote not closed\n");
		return (0);
	}
	if (data->double_quote)
	{
		printf("quote not closed\n");
		return (0);
	}
	return (1);
}
