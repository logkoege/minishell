/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_chainlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:20:11 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/31 17:47:53 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_single_quote(char *str, int *i, int *j, char *new)
{
	(*i)++;
	while (str[*i] != '\'')
	{
		new[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

static void	handle_double_quote(char *str, int *i, int *j, char *new)
{
	(*i)++;
	while (str[*i] != '\"')
	{
		new[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

char	*delete_quote(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'')
			handle_single_quote(str, &i, &j, new);
		else if (str[i] == '\"')
			handle_double_quote(str, &i, &j, new);
		else
		{
			new[j] = str[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}

t_cmd	*first_to_cmd(t_data *data)
{
	t_first	*tmp;
	t_cmd	*cmd;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	tmp = data->first;
	cmd = lst_new_cmd(data);
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			cmd->arg[i] = NULL;
			cmd->file[j] = NULL;
			lstadd_back_cmd(&cmd, lst_new_cmd(data));
			cmd = cmd->next;
			k = 0;
			i = 0;
			j = 0;
		}
		if (tmp->token == HEREDOC || tmp->token == TRUNC
			|| tmp->token == INPUT || tmp->token == APPEND)
		{
			cmd->tkn[k] = tmp->token;
			cmd->tkn[k + 1] = 0;
			tmp = tmp->next;
			cmd->file[j] = delete_quote(tmp->str);
			if (cmd->file[j][0] != '\0')
			{
				cmd->file[j + 1] = NULL;
				j++;
				k++;
			}
			else
				free(cmd->file[j]);
		}
		else if (tmp->token == WORD)
		{
			cmd->arg[i] = delete_quote(tmp->str);
			if (cmd->arg[i][0] != '\0')
			{
				cmd->arg[i + 1] = NULL;
				cmd->tkn[k] = tmp->token;
				cmd->tkn[k + 1] = 0;
				i++;
				k++;
			}
			else
				free(cmd->arg[i]);
			cmd->file[j] = NULL;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		cmd->arg[i] = NULL;
		cmd->file[j] = NULL;
		cmd->tkn[k] = 0;
		cmd->next = NULL;
	}
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}
