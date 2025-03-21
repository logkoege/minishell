/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:08:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/20 18:33:57 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_structs(t_data *data)
{
	free(data);
}

void	free_all(t_data *data)
{
	t_env	*tmp3;

	while (data->env)
	{
		tmp3 = data->env;
		data->env = data->env->next;
		free(tmp3->before_eq);
		free(tmp3->after_eq);
		free(tmp3);
	}
	free_structs(data);
}

void	free_struct(t_data *data)
{
	t_first	*tmp;
	t_cmd	*tmp2;
	int		i;

	while (data->cmd)
	{
		i = 0;
		tmp2 = data->cmd;
		data->cmd = data->cmd->next;
		while (tmp2->arg[i])
		{
			free(tmp2->arg[i]);
			i++;
		}
		free(tmp2->arg);
		i = 0;
		while (tmp2->file[i])
		{
			free(tmp2->file[i]);
			i++;
		}
		free(tmp2->file);
		free(tmp2->tkn);
		free(tmp2);
	}
	while (data->first)
	{
		i = 0;
		tmp = data->first;
		data->first = data->first->next;
		free(tmp->str);
		free(tmp);
	}
}
