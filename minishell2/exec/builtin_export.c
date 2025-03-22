/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:47:20 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/22 17:19:58 by levaipro         ###   ########.fr       */
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
char *malloc_export_eq(char *export, t_env *env)
{
	char *tmp;
	char *tmp1;
	char *tmp2;

	tmp = ft_strjoin(env->before_eq, "=");
	tmp1 = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp2 = ft_strjoin(tmp1, env->after_eq);
	free(tmp1);
	export = ft_strjoin(tmp2, "\"");
	free(tmp2);
	return(export);
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
	// printf("i = %d", i);
	env = env_1;
	export = malloc(sizeof(char *) * (i + 2));
	if(!export)
	{
		printf("export malloc error \n");
		return(NULL);
	}
	i = 0;
	while(env)
	{
		if(env->equal == 1)
			export[i] = malloc_export_eq(export[i], env);
		else
			export[i] = ft_dup(env->all);
		env = env->next;
		i++;
	}
	export[i] = NULL;
	return(export);
}
int	is_eauql(char *arg)
{
	int i;
	
	i = 0;

	while(arg[i])
	{
		if(arg[i] == '=')
			return(i);
		i++;
	}
	return(0);
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
	// int eq;
	// int j;

	// j = 0;
	// eq = 0;
	i = 0;
	while(export[i])
	{
		// printf("eq = %d\n", is_eauql(export[i]));
		printf("declare -x %s\n", export[i]);
		i++;
	}
	
}
void	free_export(char **export)
{
	int i;

	i = 0;
	while(export[i])
	{
		free(export[i]);
		export[i] = NULL;
		i++;
	}
	free(export);
	export = NULL;
}

int check_export(char *arg, t_env *env)
{
	int i;
	int eq;

	i = 0;
	eq = is_eauql(arg);
	eq++;
	if(is_digit(arg[1]) == 1)
		return(1);
	while(i != eq)
	{
		if(arg[i] == '.' || arg[i] == '-')
			return(1);
		i++;
	}
	if(ft_getenv(arg, env, 1) != NULL)
		return(2);
	return(0);
}

t_env	*buitlin_export(t_env *env, t_cmd *cmd)
{
	// int i;
	char **export;
	// (void)export;
	// i = 0;
	// t_env *exprt;
	// exprt = env;
	(void)env;
	
	
	if(cmd->arg[1] == NULL)
	{
		export = malloc_export(env);
		sort_export(export, env);
		print_export(export);
		free_export(export);
	}
	else
	{
		if(check_export(cmd->arg[1], env) == 1)
		{
			errno = EINVAL;
			perror("export ");
			return(env);
		}
		else if(check_export(cmd->arg[1], env) == 2)
			return(env);
		else
			lstadd_back_env(&env, lst_new_env(cmd->arg[1]));
		
		
	}
	// env = exprt;
	// while(exprt)
	// {
	// 	printf("before : %s\n after : %s\n all : %s\n", exprt->before_eq, exprt->after_eq, exprt->all);
	// 	exprt = exprt->next;
	// }

	// printf("aaaa\n");
	return(env);
}

