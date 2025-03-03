/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:48:33 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/23 18:14:09 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	innit_var(t_cmd *cmd, t_env *env)
{
	cmd->arg = NULL;
	cmd->file = NULL;
	cmd->tkn = 0;
	

}