/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:46:07 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/22 22:05:20 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
