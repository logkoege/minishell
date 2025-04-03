/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:47:20 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/31 08:13:20 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check2_export(char *arg, int eq, char *env_check, t_env *env)
{
	int	i;

	i = 0;
	while (i != eq)
	{
		if (arg[i] == '.' || arg[i] == '-')
			return (free(env_check), 1);
		i++;
	}
	if (ft_getenv(env_check, env, 1) != NULL)
		return (free(env_check), 2);
	free(env_check);
	return (0);
}

int	check_export(char *arg, t_env *env)
{
	int		i;
	int		eq;
	char	*env_check;

	i = 0;
	eq = is_eauql(arg);
	if (arg[0] == '=')
		return (1);
	if (eq != 0)
		env_check = ft_sub(arg, 0, ft_strlen(arg)
				- ft_strlen(ft_chr(arg, '=')));
	else
	{
		if (export_syntax(arg, i) == 1)
			return (1);
		env_check = ft_dup(arg);
	}
	eq++;
	if (is_digit(arg[0]) == 1 || arg[0] == '=')
		return (free(env_check), 1);
	return (check2_export(arg, eq, env_check, env));
}

t_env	*builtin_export(t_env *env, t_cmd *cmd)
{
	char	**export;

	if (cmd->arg[1] == NULL)
	{
		export = malloc_export(env);
		sort_export(export, env);
		print_export(export);
		free_export(export);
	}
	else
	{
		if (check_export(cmd->arg[1], env) == 1)
		{
			errno = EINVAL;
			perror("export ");
			g_exit_code = 1;
			return (env);
		}
		else if (check_export(cmd->arg[1], env) == 2)
			return (unset_export(env, cmd->arg[1]));
		else
			lstadd_back_env(&env, lst_new_env(cmd->arg[1]));
	}
	return (env);
}
