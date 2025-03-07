// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   chain_lists.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/03 18:51:55 by lloginov          #+#    #+#             */
// /*   Updated: 2025/02/06 17:26:25 by lloginov         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// t_env	*list_env(char **envp)
// {
// 	int		i;
// 	t_env	*env;

// 	env = NULL;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		lstadd_back_env(&env, lst_new_env(envp[i]));
// 		i++;
// 	}
// 	return(env);
// }

// t_env	*lst_new_env(char *envp)
// {
// 	t_env	*lst;

// 	lst = malloc(sizeof(t_env));
// 	if (!lst)
// 		return (NULL);
// 	lst->before_eq = ft_sub(envp, 0, ft_strlen(envp)
// 			- ft_strlen(ft_chr(envp, '=')));
// 	lst->after_eq = ft_chr(envp, '=') + 1;
// 	lst->all = ft_dup(envp);
// 	lst->next = NULL;
// 	return (lst);
// }

// void	lstadd_back_env(t_env **lst, t_env *new)
// {
// 	t_env	*last;

// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last = lstlast_env(*lst);
// 	last->next = new;
// }

// t_env	*lstlast_env(t_env *lst)
// {
// 	while (lst != NULL)
// 	{
// 		if (lst->next == NULL)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (NULL);
// }