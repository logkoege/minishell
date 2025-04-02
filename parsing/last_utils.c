/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:09:11 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/02 18:35:13 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_null(t_cmd *cmd, t_data *data)
{
	cmd->arg[data->a] = NULL;
	cmd->file[data->f] = NULL;
	cmd->tkn[data->t] = 0;
	cmd->next = NULL;
}

t_cmd	*pipe_cmd(t_data *data, t_first *tmp, t_cmd *cmd)
{
	(void)tmp;
	cmd->arg[data->a] = NULL;
	cmd->file[data->f] = NULL;
	lstadd_back_cmd(&cmd, lst_new_cmd(data));
	cmd = cmd->next;
	data->t = 0;
	data->a = 0;
	data->f = 0;
	return (cmd);
}

void	file_cmd(t_data *data, t_first *tmp, t_cmd *cmd)
{
	cmd->tkn[data->t] = tmp->token;
	cmd->tkn[data->t + 1] = 0;
	tmp = tmp->next;
	cmd->file[data->f] = delete_quote(tmp->str);
	if (cmd->file[data->f][0] != '\0')
	{
		cmd->file[data->f + 1] = NULL;
		data->f++;
		data->t++;
	}
	else
		free(cmd->file[data->f]);
}

void	word_cmd(t_data *data, t_first *tmp, t_cmd *cmd)
{
	cmd->arg[data->a] = delete_quote(tmp->str);
	if (cmd->arg[data->a][0])
	{
		cmd->arg[data->a + 1] = NULL;
		cmd->tkn[data->t] = tmp->token;
		cmd->tkn[data->t + 1] = 0;
		data->a++;
		data->t++;
	}
	else
		free(cmd->arg[data->a]);
	cmd->file[data->f] = NULL;
}

t_cmd	*first_to_cmd(t_data *data)
{
	t_first	*tmp;
	t_cmd	*cmd;

	data->t = 0;
	data->a = 0;
	data->f = 0;
	tmp = data->first;
	cmd = lst_new_cmd(data);
	while (tmp)
	{
		if (tmp->token == PIPE)
			cmd = pipe_cmd(data, tmp, cmd);
		if (tmp->token == HEREDOC || tmp->token == TRUNC
			|| tmp->token == INPUT || tmp->token == APPEND)
			file_cmd(data, tmp, cmd);
		else if (tmp->token == WORD)
			word_cmd(data, tmp, cmd);
		tmp = tmp->next;
	}
	if (tmp == NULL)
		set_null(cmd, data);
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}
/*
t_cmd	*first_to_cmd(t_data *data)
{
	t_first	*tmp;
	t_cmd	*cmd;

	data->t = 0;
	data->a = 0;
	data->f = 0;
	tmp = data->first;
	cmd = lst_new_cmd(data);
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			cmd->arg[data->a] = NULL;
			cmd->file[data->f] = NULL;
			lstadd_back_cmd(&cmd, lst_new_cmd(data));
			cmd = cmd->next;
			data->t = 0;
			data->a = 0;
			data->f = 0;
		}
		if (tmp->token == HEREDOC || tmp->token == TRUNC
			|| tmp->token == INPUT || tmp->token == APPEND)
		{
			cmd->tkn[data->t] = tmp->token;
			cmd->tkn[data->t + 1] = 0;
			tmp = tmp->next;
			cmd->file[data->f] = delete_quote(tmp->str);
			if (cmd->file[data->f][0] != '\0')
			{
				cmd->file[data->f + 1] = NULL;
				data->f++;
				data->t++;
			}
			else
				free(cmd->file[data->f]);
		}
		else if (tmp->token == WORD)
		{
			cmd->arg[data->a] = delete_quote(tmp->str);
			if (cmd->arg[data->a][0])
			{
				cmd->arg[data->a + 1] = NULL;
				cmd->tkn[data->t] = tmp->token;
				cmd->tkn[data->t + 1] = 0;
				data->a++;
				data->t++;
			}
			else
				free(cmd->arg[data->a]);
			cmd->file[data->f] = NULL;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		cmd->arg[data->a] = NULL;
		cmd->file[data->f] = NULL;
		cmd->tkn[data->t] = 0;
		cmd->next = NULL;
	}
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}*/