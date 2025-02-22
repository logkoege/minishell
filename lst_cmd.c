/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:20:51 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/22 21:50:08 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*lst_new_cmd(t_data *data)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->arg = malloc(sizeof(char *) * data->lst_size + 1);
	new->tkn = malloc(sizeof(int) * data->lst_size + 1);
	new->file = malloc(sizeof(char *) * (data->lst_size / 2) + 1);
	new->tkn[0] = 0;
	new->next = NULL;
	return (new);
}

t_cmd	*lstlast_cmd(t_cmd *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_cmd	*lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!*lst)
	{
		*lst = new;
		return (*lst);
	}
	last = lstlast_cmd(*lst);
	last->next = new;
	return (last);
}
