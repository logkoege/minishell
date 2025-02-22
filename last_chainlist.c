/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_chainlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:20:11 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/22 22:02:27 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			i++;
			while (str[i] != '\'')
			{
				new[j++] = str[i++];
				i++;
				j++;
			}
			i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				new[j] = str[i];
				i++;
				j++;
			}
			i++;
		}
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

void	first_to_cmd(t_data *data)
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
			print_lst_cmd(cmd);
			lstadd_back_cmd(&cmd, lst_new_cmd(data));
			k = 0;
			i = 0;
			j = 0;
		}
		else if (tmp->token == HEREDOC || tmp->token == TRUNC || tmp->token == INPUT || tmp->token == APPEND)
		{
			cmd->tkn[k] = tmp->token;
			cmd->tkn[k + 1] = 0;
			tmp = tmp->next;
			cmd->file[j] = tmp->str;
			j++;
			k++;
		}
		else
		{
			cmd->arg[i] = delete_quote(tmp->str);
			cmd->tkn[k] = tmp->token;
			i++;
			k++;
		}
		tmp = tmp->next;
		if (tmp == NULL)
		{
			cmd->arg[i] = NULL;
			cmd->file[j] = NULL;
		}
	}
	print_lst_cmd(cmd);
}

void	print_lst_cmd(t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	while (cmd)
	{
		i = 0;
		j = 0;
		while (cmd->arg[i])
		{
			printf("arg[%d] = %s\n", i, cmd->arg[i]);
			i++;
		}
		while (cmd->file[j])
		{
			printf("file[%d] = %s\n", j, cmd->file[j]);
			j++;
		}
		while (cmd->tkn[k])
		{
			printf("tkn[%d] = %d\n", k, cmd->tkn[k]);
			k++;
		}
		cmd = cmd->next;
	}
}
