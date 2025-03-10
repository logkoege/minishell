/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:41:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/10 11:41:32 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_fprintf(char *str)
{
	int len;
	len = ft_strlen(str);
	write(2, str, len);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;

	while(s2[i])
	{
		if(s1[i]!= s2[i])
			return(1);
		i++;
	}
	return(0);
}