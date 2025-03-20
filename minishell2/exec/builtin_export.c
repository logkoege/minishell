/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:47:20 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/20 23:17:07 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmxport(char *s1,char *s2)
{
	int	i;

	i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char 	**malloc_export(t_env *env)
{
	t_env *env_1;
	int i;
	char **export;
	export = NULL;
	
	i = 0;
	env_1 = env;
	while(env)
	{
		env = env->next;
		i++;
	}
	env = env_1;
	export = malloc(sizeof(char *) * (i + 1));
	if(!export)
	{
		printf("export malloc error \n");
		return(NULL);
	}
	i = 0;
	while(env)
	{
		export[i] = malloc(sizeof(char) * (ft_strlen(env->all) + 1));
		if(!export[i])
		{
			printf("errror on export %d", i);
			exit(1);
		}
		export[i] = ft_dup(env->all);
		env = env->next;
		i++;
	}
	export[i] = NULL;
	return(export);
}
void	sort_export(char **export, t_env *env)
{
	int i;
	int j;
	char *tmp;

	j = 1;
	i = 0;
	(void)env;

	while (export[i])
	{
		j = i + 1;
		while (export[j])
		{
			if (ft_strcmxport(export[i], export[j]) > 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
}
void	print_export(char **export)
{
	int i;

	i = 0;
	while(export[i])
	{
		printf("declare -x %s\n", export[i]);
		i++;
	}
	
}

t_env	*buitlin_export(t_env *env, t_cmd *cmd)
{
	// int i;
	char **export;
	// (void)export;
	// i = 0;
	(void)env;

	if(cmd->arg[1] == NULL)
	{
		export = malloc_export(env);
		sort_export(export, env);
		print_export(export);
	}
	else
	{
		
	}
	return(env);
}

