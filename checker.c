/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:04:45 by logkoege          #+#    #+#             */
/*   Updated: 2025/01/20 16:46:40 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *input , t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && (data->single_quote == false && data->double_quote == false))
		{
			i++;
			while (input[i] && is_ws(input[i]))
				i++;
			if (input[i] == '|' || input[i] == '\0')
			{
				printf("syntax4 error near unexpected token '|'\n");
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}

int	check_double_redirect(char *input, t_data *data)
{
	int	i;

	i = 0;
	if (data->double_quote != false || data->single_quote != false)
	{
		while (input[i])
		{
			i += skip_quote(&input[i], data);
			if ((input[i] == '>' && input[i + 1] == '>')
				|| (input[i] == '<' && input[i + 1] == '<'))
			{
				i += 2;
				while (input[i] && is_ws(input[i]))
					i++;
				if (input[i] == '>' || input[i] == '<'
					|| input[i] == '|' || input[i] == '\0')
				{
					printf("syntax3 error\n");
					return (0);
				}
			}
			else
				i++;
		}
	}
	return (1);
}

int	check_other(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i += skip_quote(&input[i], data);
		if ((input[i] == '>' || input[i] == '<')
			&& (input[i + 1] != '>' && input[i + 1] != '<'))
		{
			i++;
			while (input[i] && is_ws(input[i]))
				i++;
			if (input[i] == '>' || input[i] == '<'
				|| input[i] == '|' || input[i] == '\0')
			{
				printf("syntax1 error\n");
				return (0);
			}
		}
		if (data->single_quote == false && data->double_quote == false)
		{
			if (check_double_redirect(&input[i], data) == 0 )
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_invalid_combinations(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i += skip_quote(&input[i], data);
		if (data->double_quote == false && data->single_quote == false)
		{
			if (((input[i] == '>') && (input[i + 1] == '<'))
				|| ((input[i] == '<') && (input[i + 1] == '>')))
			{
				printf("syntax2 error\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	track(int *i, int *j, char *input, char n)
{
	if (input[*i] == n)
	{
		if (*i != 0 && input[*i - 1] != ' ')
			(*j)++;
		if (input[*i + 1] == n)
		{
			(*i)++;
			if (input[*i + 1] != ' ' && input[*i])
			{
				(*j)++;
			}
		}
		else if (input[*i + 1] != ' ' && input[*i + 1] != '\0')
			(*j)++;
	}
}
