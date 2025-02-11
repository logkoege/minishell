/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:42 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/11 17:08:05 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_first	*lstnew(int token, char *ssr)
{
	t_first	*lst;

	lst = malloc(sizeof(t_first));
	if (!lst)
		return (NULL);
	lst->token = token;
	lst->str = ssr;
	lst->next = NULL;
	return (lst);
}

void	lstadd_back(t_first **lst, t_first *new)
{
	t_first	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last->next = new;
}

t_first	*lstlast(t_first *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
