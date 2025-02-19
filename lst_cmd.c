/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:20:51 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/19 19:26:50 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->tkn = 0;
	new->arg = NULL;
	new->file = NULL;
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
