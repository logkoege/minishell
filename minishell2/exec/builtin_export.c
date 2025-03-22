/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:47:20 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/21 18:56:13 by levaipro         ###   ########.fr       */
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
			return(i + 1);
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


t_env	*lst_new_env2(char *envp)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	if(is_eauql(envp) == 0)
	{
		lst->before_eq = ft_dup(envp);
		lst->after_eq = NULL;
		lst->all = ft_dup(envp);
		lst->equal = 0;
	}
	else
	{
		lst->before_eq = ft_sub(envp, 0, ft_strlen(envp) - ft_strlen(ft_chr(envp, '=')));
		lst->after_eq = ft_chr(envp, '=') + 1;
		printf("lst after : %s\n", lst->after_eq);
		if(lst->after_eq == NULL)
			lst->equal = 0;
		else
			lst->equal = 1;
		lst->all = ft_dup(envp);
		lst->next = NULL;
	}
	return (lst);
}
int check_export(char *arg)
{
	int i;
	int eq;

	i = 0;
	eq = is_eauql(arg);
	
	if(is_digit(arg[1]) == 1)
		return(1);
	while(i != eq)
	{
		if(arg[i] == '.' || arg[i] == '-')
			return(1);
		i++;
	}
	return(0);
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
		free_export(export);
	}
	else
	{
		if(check_export(cmd->arg[1]) == 1)
		{
			errno = EINVAL;
			perror("export ");
			return(env);
		}
		lstadd_back_env(&env, lst_new_env(cmd->arg[1]));
		
	}

	// printf("aaaa\n");
	return(env);
}

