/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:40:48 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/31 19:05:51 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	copy_prefix(t_first *tmp2, char *str, int i)
{
	int	j;

	j = 0;
	if (i <= 0)
		return (0);
	while (j < i - 1)
	{
		str[j] = tmp2->str[j];
		j++;
	}
	return (j);
}

void	handle_special_case(char *str, int *j, t_data *data)
{
	int	c;

	if (!data->new_str)
		return ;
	c = 0;
	while (data->new_str[c])
		str[(*j)++] = data->new_str[c++];
	str[*j] = '\0';
	//free(data->new_str);
}

int	handle_digit_or_quote(t_first *tmp2, int i, t_data *data)
{
	char	*new_str;

	(void)data;
	if (is_digit(tmp2->str[i]))
	{
		new_str = ft_dup_digit(tmp2->str, i - 1);
		if (!new_str)
			return (-1);
		free(tmp2->str);
		tmp2->str = new_str;
		return (0);
	}
	// if ((data->quote && tmp2->str[i] == '"')
	// 	|| (!data->quote && (tmp2->str[i] == '"' || tmp2->str[i] == '\'')))
	// 	return (1);
	return (-1);
}

int	handle_dollar_cases(t_first *tmp2, int *i, t_data *data)
{
	if (tmp2->str[*i] == '?')
	{
		data->new_str = ft_itoa(g_exit_code);
	}
	else if (tmp2->str[*i] == '$')
		data->new_str = ft_itoa(getpid());
	else if (data->quote && tmp2->str[*i] == '\'')
		return (-1);
	else
		return (-1);
	if (!data->new_str)
		return (-1);
	(*i)++;
	return (0);
}

void	copy_remaining_str(t_first *tmp2, char *str, int *i, int *j)
{
	while (tmp2->str[*i] && tmp2->str[*i] != '$' && tmp2->str[*i] != ' '
		&& tmp2->str[*i] != '"' && tmp2->str[*i] != '\'')
		(*i)++;
	while (tmp2->str[*i])
		str[(*j)++] = tmp2->str[(*i)++];
	str[*j] = '\0';
}
