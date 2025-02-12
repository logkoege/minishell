/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:20:51 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/12 14:18:46 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*lst_new_cmd(int *tkn, char **arg, char **file, bool skip_cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->tkn = tkn;
	new->arg = arg;
	new->file = file;
	new->skip_cmd = skip_cmd;
	new->next = NULL;
	return (new);
}
