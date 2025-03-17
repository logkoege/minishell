/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:41:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/17 23:00:51 by levaipro         ###   ########.fr       */
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

	while(s2[i])
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
		res[i] = ft_dup(env->all);
		i++;
		env = env->next;
	}
	res[i] = NULL;
	return(res);
}
