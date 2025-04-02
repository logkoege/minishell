/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:11:46 by levaipro          #+#    #+#             */
/*   Updated: 2025/03/31 15:20:04 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmxport(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*malloc_export_eq(char *export, t_env *env)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	tmp = ft_strjoin(env->before_eq, "=");
	tmp1 = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp2 = ft_strjoin(tmp1, env->after_eq);
	free(tmp1);
	export = ft_strjoin(tmp2, "\"");
	free(tmp2);
	return (export);
}

int	get_export_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**malloc_export(t_env *env)
{
	t_env	*env_1;
	int		i;
	char	**export;

	export = NULL;
	env_1 = env;
	i = get_export_size(env_1);
	export = malloc(sizeof(char *) * (i + 1));
	if (!export)
	{
		printf("export malloc error\n");
		return (NULL);
	}
	i = 0;
	while (env)
	{
		if (env->equal == 1)
			export[i] = malloc_export_eq(export[i], env);
		else
			export[i] = ft_dup(env->all);
		env = env->next;
		i++;
	}
	export[i] = NULL;
	return (export);
}

int	is_eauql(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
