/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:46:07 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/24 15:31:14 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*list_env(char **envp, t_env **env)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		lstadd_back_env(env, lst_new_env(envp[i]));
		i++;
	}
	return (*env);
}

t_env	*lst_new_env(char *envp)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	if (is_eauql(envp) == 0)
	{
		//printf("equal\n");
		lst->all = ft_dup(envp);
		lst->before_eq = lst->all;
		lst->after_eq = NULL;
		lst->equal = 0;
		lst->next = NULL;
		return(lst);
	}
	lst->before_eq = ft_dup(ft_sub(envp, 0, ft_strlen(envp)
			- ft_strlen(ft_chr(envp, '='))));
	lst->after_eq = ft_dup(ft_chr(envp, '=') + 1);
	lst->equal = 1;
	// printf("afet eq : %s\n", lst->after_eq);
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

void	print_lst_first(t_data *data)
{
	t_first	*print;

	print = data->first;
	data->lst_size = 0;
	while (print)
	{
		data->lst_size++;
		//printf("str = %s\n", print->str);
		//printf("token = %d\n", print->token);
		print = print->next;
	}
}
