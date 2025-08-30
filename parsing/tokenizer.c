/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:36 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/03 18:38:02 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokenizer_utils(char *str, char n)
{
	int	i;

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
	int	i;

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
