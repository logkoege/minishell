/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:08:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/10 16:47:00 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_structs(t_data *data)
{
	free(data);
}

void	free_all(t_data *data)
{
	free_structs(data);
}

void	free_struct(t_data *data)
{
	t_first	*tmp;

	while (data->first)
	{
		tmp = data->first;
		data->first = data->first->next;
		free(tmp->str);
		free(tmp);
	}
}
