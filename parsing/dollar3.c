/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:54:27 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/03 14:21:14 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mid_rmv(t_first *tmp2, char *str, int i)
{
	if (is_digit(tmp2->str[i]))
	{
		free(str);
		str = ft_dup_digit(tmp2->str, i - 1);
		free(tmp2->str);
		tmp2->str = ft_dup(str);
		free(str);
		return (0);
	}
	else if (tmp2->str[i] == '\"' || tmp2->str[i] == '\''
		|| tmp2->str[i] == ' ' || tmp2->str[i] == '\0')
	{
		free(str);
		str = ft_dup(tmp2->str);
		free(tmp2->str);
		tmp2->str = ft_dup(str);
		free(str);
		return (1);
	}
	return (0);
}

void	minidoll(char *str, int j, t_first *tmp2, char *str2)
{
	str[j] = '\0';
	free(tmp2->str);
	tmp2->str = str;
	free(str2);
}

int	doll(char *str, t_first *tmp2, int i, int j)
{
	char	*str2;
	int		c;

	c = 0;
	if (tmp2->str[i] == '?')
	{
		str2 = ft_itoa(g_exit_code);
		while (str2[c])
			str[j++] = str2[c++];
		while (tmp2->str[++i])
			str[j++] = tmp2->str[i];
		minidoll(str, j, tmp2, str2);
		return (0);
	}
	else if (tmp2->str[i] == '$')
	{
		str2 = ft_itoa(getpid());
		while (str2[c])
			str[j++] = str2[c++];
		while (tmp2->str[++i])
			str[j++] = tmp2->str[i];
		minidoll(str, j, tmp2, str2);
		return (0);
	}
	return (1);
}

int	remove_dollar(t_first *tmp2, char *str, int i)
{
	int	j;

	j = -1;
	while (++j < i - 1)
		str[j] = tmp2->str[j];
	if (doll(str, tmp2, i, j) == 0)
		return (0);
	else if (is_digit(tmp2->str[i])
		|| tmp2->str[i] == '\"' || tmp2->str[i] == '\''
		|| tmp2->str[i] == ' ' || tmp2->str[i] == '\0')
		return (mid_rmv(tmp2, str, i));
	i++;
	while (tmp2->str[i] != '$' && tmp2->str[i] != ' ' && tmp2->str[i] != '\0'
		&& tmp2->str[i] != '\"' && tmp2->str[i] != '\'')
		i++;
	while (tmp2->str[i])
	{
		str[j] = tmp2->str[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(tmp2->str);
	tmp2->str = str;
	return (0);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
