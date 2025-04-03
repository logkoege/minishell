/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:08:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/02 20:25:52 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	free(data);
	rl_clear_history();
}

void	free_cmd_arg(t_cmd *tmp2, int i)
{
	if (tmp2->arg)
	{
		while (tmp2->arg[i])
		{
			free(tmp2->arg[i]);
			i++;
		}
		free(tmp2->arg);
	}
}

void	free_cmd_file(t_cmd *tmp2, int i)
{
	if (tmp2->file)
	{
		while (tmp2->file[i])
		{
			free(tmp2->file[i]);
			i++;
		}
		free(tmp2->file);
	}
}

void	free_struct(t_data *data, t_cmd *cmd)
{
	t_cmd	*tmp2;
	int		i;

	if (cmd)
	{
		while (cmd)
		{
			i = 0;
			tmp2 = cmd;
			cmd = cmd->next;
			free_cmd_arg(tmp2, i);
			free_cmd_file(tmp2, i);
			free(tmp2->tkn);
			free(tmp2);
		}
	}
	fri_te(data);
}

void	fri_te(t_data *data)
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
