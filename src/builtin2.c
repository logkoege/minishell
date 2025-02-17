/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:12:18 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/17 17:59:21 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	buitlin_env(t_env *env)
{
	t_env *tmp;

	// while(tmp)
	// {
	// 	printf("%s\n", tmp->all);
	// 	tmp = tmp->next;
	// }

}

void	builtin_exit(t_cmd *cmd)
{
	printf("%s\n", cmd->arg);
	exit(0);
}

void	builtin_export(t_cmd *cmd, t_env *env)
{
	t_xport *xport;

	xport = env;

	int i;
	int j;

	j = 0;
	i = 0;
	xport = sortxport(xport, NULL);
	// while(xport)
	// {
	// 	printf("%s\n", xport->all);
	// 	xport = xport->next;
	// }
	
}

t_xport *sortxport(t_xport *xport, char *new)
{
	t_xport *head;

	char *tmp;
	while(xport)
	{
		
	}
	return(xport);
}