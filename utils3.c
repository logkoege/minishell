/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:29:00 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/05 17:32:22 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_chr(char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*ft_dup(char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_sub(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_dup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
