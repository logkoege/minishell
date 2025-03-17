/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_chainlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:20:11 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/17 22:58:02 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				new[j] = str[i];
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
			cmd->file[j] = tmp->str;
			cmd->file[j + 1] = NULL;
			j++;
			k++;
		}
		else if (tmp->token == WORD)
		{

			cmd->arg[i] = delete_quote(tmp->str);
			cmd->arg[i + 1] = NULL;
			cmd->tkn[k] = tmp->token;
			cmd->tkn[k + 1] = 0;
			cmd->file[j] = NULL;
			i++;
			k++;
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
	//print_lst_cmd(cmd);
	return (cmd);
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
		k = 0;
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
		// printf("cmd : infile : %d : out %d\n", cmd->outfile, cmd->infile);
		cmd = cmd->next;
	}
}
