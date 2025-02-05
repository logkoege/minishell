/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:51:55 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/05 18:49:49 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	list_env(char **envp)
{
	int		i;
	t_env	*env;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		lstadd_back_env(&env, lst_new_env(envp[i]));
		i++;
	}
	while(env->next != NULL)
	{
		if(strcmp( env->before_eq, "PWD") == 0)
		{
			env->all = "caca";
			printf("VOICI : %s\n", env->all);
		}
		env = env->next;
	}
	printf("\n\n\n\n\n\n");
	env 
	while(env->next != NULL)
	{
		printf("VOICI : %s\n", env->all);
		env = env->next;
	}
}

t_env	*lst_new_env(char *envp)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->before_eq = ft_sub(envp, 0, ft_strlen(envp)
			- ft_strlen(ft_chr(envp, '=')));
	lst->after_eq = ft_chr(envp, '=') + 1;
	lst->all = ft_dup(envp);
	lst->next = NULL;
	return (lst);
}

void	lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast_env(*lst);
	last->next = new;
}

t_env	*lstlast_env(t_env *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}