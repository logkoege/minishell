/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_chainlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:20:11 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/02 18:49:49 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*utils_delete(int *i, int *j, char *str, char *new)
{
	if (str[(*i)] == '\'' && str[(*i) + 1] != '\0')
	{
		(*i)++;
		while (str[(*i)] != '\'' && str[(*i)] != '\0')
		{
			new[(*j)] = str[(*i)];
			(*i)++;
			(*j)++;
		}
		(*i)++;
	}
	return (new);
}

char	*utils_delete2(int *i, int *j, char *str, char *new)
{
	if (str[(*i)] == '\"' && str[(*i) + 1] != '\0')
	{
		(*i)++;
		while (str[(*i)] != '\"' && str[(*i)] != '\0')
		{
			new[(*j)] = str[(*i)];
			(*i)++;
			(*j)++;
		}
		(*i)++;
	}
	return (new);
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
		new = utils_delete(&i, &j, str, new);
		if (str[i] == '\0')
			break ;
		new = utils_delete2(&i, &j, str, new);
		if (str[i] == '\0')
			break ;
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

// t_cmd	*first_to_cmd(t_data *data)
// {
// 	t_first	*tmp;
// 	t_cmd	*cmd;

// 	data->t = 0;
// 	data->a = 0;
// 	data->f = 0;
// 	tmp = data->first;
// 	cmd = lst_new_cmd(data);
// 	while (tmp)
// 	{
// 		if (tmp->token == PIPE)
// 		{
// 			cmd->arg[data->a] = NULL;
// 			cmd->file[data->f] = NULL;
// 			lstadd_back_cmd(&cmd, lst_new_cmd(data));
// 			cmd = cmd->next;
// 			data->t = 0;
// 			data->a = 0;
// 			data->f = 0;
// 		}
// 		if (tmp->token == HEREDOC || tmp->token == TRUNC
// 			|| tmp->token == INPUT || tmp->token == APPEND)
// 		{
// 			cmd->tkn[data->t] = tmp->token;
// 			cmd->tkn[data->t + 1] = 0;
// 			tmp = tmp->next;
// 			cmd->file[data->f] = delete_quote(tmp->str);
// 			if (cmd->file[data->f][0] != '\0')
// 			{
// 				cmd->file[data->f + 1] = NULL;
// 				data->f++;
// 				data->t++;
// 			}
// 			else
// 				free(cmd->file[data->f]);
// 		}
// 		else if (tmp->token == WORD)
// 		{
// 			cmd->arg[data->a] = delete_quote(tmp->str);
// 			if (cmd->arg[data->a][0])
// 			{
// 				cmd->arg[data->a + 1] = NULL;
// 				cmd->tkn[data->t] = tmp->token;
// 				cmd->tkn[data->t + 1] = 0;
// 				data->a++;
// 				data->t++;
// 			}
// 			else
// 				free(cmd->arg[data->a]);
// 			cmd->file[data->f] = NULL;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (tmp == NULL)
// 	{
// 		cmd->arg[data->a] = NULL;
// 		cmd->file[data->f] = NULL;
// 		cmd->tkn[data->t] = 0;
// 		cmd->next = NULL;
// 	}
// 	while (cmd->prev)
// 		cmd = cmd->prev;
// 	return (cmd);
// }

// void	print_lst_cmd(t_cmd *cmd)
// {
// 	int		i;
// 	int		j;
// 	int		k;

// 	k = 0;
// 	i = 0;
// 	j = 0;
// 	while (cmd)
// 	{
// 		i = 0;
// 		j = 0;
// 		k = 0;
// 		while (cmd->arg[i])
// 		{
// 			printf("arg[%d] = %s\n", i, cmd->arg[i]);
// 			i++;
// 		}
// 		while (cmd->file[j])
// 		{
// 			printf("file[%d] = %s\n", j, cmd->file[j]);
// 			j++;
// 		}
// 		while (cmd->tkn[k])
// 		{
// 			printf("tkn[%d] = %d\n", k, cmd->tkn[k]);
// 			k++;
// 		}
// 		cmd = cmd->next;
// 	}
// }
