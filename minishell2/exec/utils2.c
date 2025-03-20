/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:41:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/20 14:29:40 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_fprintf(char *str)
{
	int len;
	len = ft_strlen(str);
	write(2, str, len);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;

	while(s1[i])
	{
		if(s1[i]!= s2[i])
			return(1);
		i++;
	}
	return(0);
}

char **env_to_str(t_env *env)
{
	char **res;
	int i;
	t_env *tmp;

	i = 0;
	tmp = env;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while(env)
	{
		// res[i] = env->all;
		res[i] = ft_dup(env->all);
		i++;
		env = env->next;
	}
	res[i] = NULL;
	return(res);
}
int ft_strcmp_echo(char *s1, char *s2)
{
	int i;

	i = 1;
	
	if(s1[1]!= s2[1])
			return(1);
	while(s1[i])
	{
		if(s1[i]!= s2[1] && s1[i] != 'e' && s1[i] != 'E')
			return(1);
		i++;
	}
	return(0);
}
