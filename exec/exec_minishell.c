/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:47:05 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/31 08:40:31 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*main_exec(t_data *data, t_env *env)
{
	data->cmd->fd_infile = 0;
	data->cmd->fd_outfile = 1;
	env = exec_1(data, env);
	return (env);
}

t_env	*check_cd(t_cmd *cmd, t_env *env, int i)
{
	i++;
	while (cmd->arg[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("bash : cd : too many argumrents\n", 2);
		g_exit_code = 1;
		return (env);
	}
	env = bultin_cd(env, cmd->arg[1]);
	return (env);
}

t_env	*check_arg(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd->arg[0], "cd") == 0)
		return (check_cd(cmd, env, i));
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		builtin_pwd(env);
	else if (ft_strcmp(cmd->arg[i], "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd->arg[i], "env") == 0)
		builtin_env(env);
	else if (ft_strcmp(cmd->arg[i], "unset") == 0)
		env = builtin_unset(env, cmd->arg[1]);
	else if (ft_strcmp(cmd->arg[i], "exit") == 0)
		builtin_exit(cmd);
	else if (ft_strcmp(cmd->arg[i], "export") == 0)
		env = builtin_export(env, cmd);
	else
		return (NULL);
	if (cmd->prev || cmd->next)
		exit(g_exit_code);
	return (env);
}

int	is_builtin(t_data *data, t_env *env)
{
	(void)env;
	if (!data->cmd->arg[0])
		return (0);
	if (ft_strcmp(data->cmd->arg[0], "cd") == 0)
		return (1);
	if (ft_strcmp(data->cmd->arg[0], "exit") == 0)
		return (1);
	if (ft_strcmp(data->cmd->arg[0], "export") == 0)
	{
		if (data->cmd->arg[1] == NULL)
			return (0);
		return (1);
	}
	if (ft_strcmp(data->cmd->arg[0], "unset") == 0)
		return (1);
	return (0);
}
