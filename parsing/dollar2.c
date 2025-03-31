/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 08:55:02 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/31 19:01:52 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static int	ft_nbrlen(int n)
{
	int	len;

	len = 1;
	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int exit_code)
{
	static int		len;
	int				is_negative;
	char			*result;

	len = ft_nbrlen(exit_code);
	is_negative = (exit_code < 0);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = ft_abs(exit_code % 10) + '0';
		exit_code /= 10;
	}
	if (is_negative)
		result[0] = '-';
	return (result);
}

int	remove_dollar(t_first *tmp2, char *str, int i, t_data *data)
{
	int		j;
	int		result;
	char	*old_str;
	char	*tmp;

	j = copy_prefix(tmp2, str, i);
	data->new_str = NULL;
	if (handle_dollar_cases(tmp2, &i, data) == 0)
	{
		handle_special_case(str, &j, data);
		tmp = tmp2->str;
		tmp2->str = ft_dupp(tmp, j, data);
		free(tmp);
		free(str);
		return (1);
	}
	result = handle_digit_or_quote(tmp2, i, data);
	if (result != -1)
		return (result);
	copy_remaining_str(tmp2, str, &i, &j);
	str[j] = '\0';
	old_str = tmp2->str;
	tmp2->str = ft_dup(str);
	free(old_str);
	free(str);
	return (1);
}

char	*ft_dupp(char *str, int j, t_data *data)
{
	char	*s2;
	int		i;
	int		k;

	k = 0;
	i = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(str) + 7));
	if (!s2)
		return (NULL);
	while (j - 1 > i)
	{
		s2[i] = str[i];
		i++;
	}
	while (data->new_str[k])
	{
		s2[i] = data->new_str[k];
		i++;
		k++;
	}
	j++;
	while (str[j])
	{
		s2[i] = str[j];
		i++;
		j++;
	}
	s2[i] = '\0';
	return (s2);
}
