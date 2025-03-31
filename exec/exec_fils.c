/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:02:31 by levaipro          #+#    #+#             */
/*   Updated: 2025/03/29 02:39:22 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	main_exec_fils(t_data *data, t_env *env)
{
	char	*path;
	char	**env_s;
	t_env	*tmp;

	set_redirects(data);
	tmp = check_arg(data->cmd, env);
	if (tmp)
		env_exit(data);
	env_s = env_to_str(env);
	path = find_path(env, data->cmd->arg[0]);
	if (!path)
		path_error(data, env, env_s);
	if (execve(path, data->cmd->arg, env_s) == 1)
		execve_exit(env, path, env_s);
}

t_env	*exec_fils(t_data *data, t_env *env, int *fd_pipe)
{
	pid_t	pid;

	(void)fd_pipe;
	pid = fork();
	if (pid == -1)
	{
		printf("Error : pid\n");
		g_exit_code = 1;
		exit(g_exit_code);
	}
	if (pid == 0)
		main_exec_fils(data, env);
	else
		redirect_pere(data, pid);
	return (env);
}
