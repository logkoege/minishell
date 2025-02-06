/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:40:50 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/06 11:53:13 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(char *src)
{
	char	*dst;
	int		i;
	int		len;

	len = ft_strlen(src);
	i = 0;
	dst = (char *)malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	count_words(char *str, char c)
{
	int	i;
	int		mot;

	i = 0;
	mot = 0;
	while (*str)
	{
		if (*str != c && mot == 0)
		{
			mot = 1;
			i++;
		}
		else if (*str == c)
			mot = 0;
		str++;
	}
	return (i);
}

char	*next_wd(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	return (&str[i]);
}

int	world_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	int	j;
	int	word_count;
	int	i;
	int	word_len;
	char	**ptr;

	word_count = count_words(s, c);
	i = 0;
	ptr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!ptr)
		return (NULL);
	while (*s && i < word_count)
	{
		s = next_wd(s, c);
		word_len = world_len(s, c);
		ptr[i] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!ptr[i])
			return (NULL);
		j = 0;
		while (j < word_len)
			ptr[i][j++] = *s++;
		ptr[i++][word_len] = '\0';
	}
	ptr[word_count] = NULL;
	return (ptr);
}