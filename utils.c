/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:01 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/25 13:26:19 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rdline(t_data *data, char **envp, t_env *env)
{
	char	*inpt;

	while (1)
	{
		inpt = readline("minishell$ ");
		if (inpt == NULL)
			exit(1);
		if (!inpt || inpt[0] == '\0')
			continue ;
		env = list_env(envp, &env);
		if (start_split(data, inpt) == NULL)
			continue ;
		setup_signals();
		add_history(inpt);
		print_lst_first(data);
		dollar_parser(data, env);
		first_to_cmd(data);
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
