/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:01 by logkoege          #+#    #+#             */
/*   Updated: 2025/01/31 16:23:24 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rdline(t_data *data)
{
	char	*inpt;

	while (1)
	{
		inpt = readline("minishell$ ");
		if (!inpt || inpt[0] == '\0')
			continue ;
		start_split(data, inpt);
		//setup_signals();
		add_history(inpt);
		// printf("str = %s\n", data->first->str);
		// printf("token = %d\n", data->first->token);
		data->single_quote = false;
		data->double_quote = false;
		free(inpt);
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
	data->first = malloc(sizeof(t_first));
	data->cmd = malloc(sizeof(t_cmd));
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
