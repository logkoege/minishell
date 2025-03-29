/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:08:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/29 19:00:26 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_structs(t_data *data)
{
	free(data);
}

void	free_all(t_data *data, t_env *env)
{
	t_env	*tmp3;

	while (env)
	{
		tmp3 = env;
		env = env->next;
		free(tmp3->before_eq);
		free(tmp3->after_eq);
		free(tmp3->all);
		free(tmp3);
	}
	free_structs(data);
}

void	free_struct(t_data *data, t_cmd *cmd)
{
	t_first	*tmp;
	t_cmd	*tmp2;

	while (cmd)
	{
		data->c = 0;
		tmp2 = cmd;
		cmd = cmd->next;
		while (tmp2->arg[data->c])
			free(tmp2->arg[data->c++]);
		free(tmp2->arg);
		data->c = 0;
		while (tmp2->file[data->c])
			free(tmp2->file[data->c++]);
		free(tmp2->file);
		free(tmp2->tkn);
		free(tmp2);
	}
	while (data->first)
	{
		tmp = data->first;
		data->first = data->first->next;
		free(tmp->str);
		free(tmp);
	}
}
