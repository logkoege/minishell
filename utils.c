/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:01 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/10 17:43:30 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rdline(t_data *data, char **envp)
{
	char	*inpt;

	while (1)
	{
		inpt = readline("minishell$ ");
		if (inpt == NULL)
			exit(1);
		if (!inpt || inpt[0] == '\0')
			continue ;
		list_env(envp);
		start_split(data, inpt);
		setup_signals();
		add_history(inpt);
		dollar_parser(data);
		while (data->first->next != NULL)
		{
			printf("str = %s\n", data->first->str);
			printf("token = %d\n", data->first->token);
			data->first = data->first->next;
		}
		printf("str = %s\n", data->first->str);
		printf("token = %d\n", data->first->token);
		free(inpt);
		free_struct(data);
		data->j = 0;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	init_var(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	data->j = 0;
	data->i = 0;
	data->single_quote = false;
	data->double_quote = false;
}

int	is_ws(char c)
{
	if ((c == ' ' ) || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	inputlen(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (i != 0 && input[i - 1] != ' '
				&& input[i - 1] != '>' && input[i - 1] != '<')
			{
				j++;
			}
			if (input[i + 1] != ' ' && input[i + 1] != '\0'
				&& input[i - 1] != '>' && input[i - 1] != '<')
			{
				j++;
			}
		}
		track(&i, &j, input, '>');
		track(&i, &j, input, '<');
		i++;
	}
	return (i + j);
}
