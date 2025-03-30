/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:11:44 by levaipro          #+#    #+#             */
/*   Updated: 2025/03/28 14:16:40 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	sort_export(char **export, t_env *env)
{
	int		i;
	int		j;
	char	*tmp;

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
	int	i;

	i = 0;
	while (export[i])
	{
		printf("declare -x %s\n", export[i]);
		i++;
	}
}

void	free_export(char **export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		free(export[i]);
		export[i] = NULL;
		i++;
	}
	free(export);
	export = NULL;
}

t_env	*unset_export(t_env *env, char *cmd)
{
	char	*unset;

	if (is_eauql(cmd) == 0)
		return (env);
	unset = ft_sub(cmd, 0, ft_strlen(cmd) - ft_strlen(ft_chr(cmd, '=')));
	env = builtin_unset(env, unset);
	free(unset);
	lstadd_back_env(&env, lst_new_env(cmd));
	return (env);
}

int	export_syntax(char *arg, int i)
{
	while (arg[i])
	{
		if (arg[i] == '.' || arg[i] == '-')
		{
			g_exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
