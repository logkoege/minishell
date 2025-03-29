/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:10:01 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/29 18:55:43 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rdline(t_data *data, t_env *env)
{
	char	*inpt;
	t_cmd	*cmd_head;

	while (1)
	{
		inpt = readline("minishell$ ");
		if (inpt == NULL)
			exit(1);
		add_history(inpt);
		if (!inpt || inpt[0] == '\0')
			continue ;
		if (start_split(data, inpt) == 0)
			continue ;
		setup_signals();
		print_lst_first(data);
		dollar_parser(data, env);
		data->cmd = first_to_cmd(data);
		// print_lst_cmd(data->cmd);
		cmd_head = data->cmd;
		env = main_exec(data, env);
		free(inpt);
		free_struct(data, cmd_head);
		data->j = 0;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	init_var(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	data->exit_code = 0;
	data->j = 0;
	data->i = 0;
	data->single_quote = false;
	data->double_quote = false;
	data->quote = false;
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
