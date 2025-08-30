/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_chainlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:20:11 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/08 14:19:20 by lloginov         ###   ########.fr       */
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

char	*delete_quote(char *str, int i)
{
	int		j;
	char	*new;

	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] != '\0')
		{
			new = utils_delete(&i, &j, str, new);
			if (str[i] == '\0')
				break ;
		}
		else if (str[i] == '\"' && str[i + 1] != '\0')
		{
			new = utils_delete2(&i, &j, str, new);
			if (str[i] == '\0')
				break ;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

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
