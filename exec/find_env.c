/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:25:31 by lloginov          #+#    #+#             */
/*   Updated: 2025/04/05 16:51:16 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_path(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

t_env	*find_env(t_cmd *exec, char **envp, t_env *env)
{
	(void)exec;
	(void)env;
	env = list_env(envp, &env);
	return (env);
}

char	*ft_getenv(char *str, t_env *env, int i)
{
	t_env	*tmp;

	tmp = env;
	if (tmp == NULL)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->before_eq, str) == 0)
		{
			if (i == 1)
				return (tmp->all);
			else if (i == 2)
				return (tmp->before_eq);
			else if (i == 3)
				return (tmp->after_eq);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
