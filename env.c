/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:46:07 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/05 14:03:30 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_env(t_data *data, char **envp)
{
	int		i;
	t_env	*env;

	i = 0;
	while (envp[i])
	{
		env = malloc(sizeof(t_env));
		if (!env)
			exit(1);
		env->tout = ft_strdup(envp[i]);
		env->avant_eq = ft_strcdup(envp[i], '=');
		env->apres_eq = ft_strchr(envp[i], '=') + 1;
		env->next = NULL;
		if (data->first->next == NULL)
			data->first->next = env;
		else
			lstadd_back(&data->first->next, env);
		i++;
	}
}