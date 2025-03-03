/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in-outfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:59:44 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/25 16:55:38 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_infile(t_cmd *exec)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while(exec->arg)
	{
		while(exec->arg[j])
		{
			if(exec->tkn[i] != 1)
			{
			}
		}
	}
}