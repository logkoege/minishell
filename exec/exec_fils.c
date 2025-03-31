/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:02:31 by levaipro          #+#    #+#             */
/*   Updated: 2025/03/31 08:16:23 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_dir(t_data *data)
{
	struct stat	statbuf;

	stat(data->cmd->arg[0], &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->cmd->arg[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_exit_code = 126;
		return (1);
	}
	return (0);
}

void	main_exec_fils(t_data *data, t_env *env)
{
	char	*path;
	char	**env_s;
	t_env	*tmp;

	set_redirects(data);
	tmp = check_arg(data->cmd, env);
	if (tmp)
		env_exit(data);
	if (is_dir(data))
		return ;
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
		ft_putstr_fd("Error : pid\n", 2);
		g_exit_code = 1;
		exit(g_exit_code);
	}
	if (pid == 0)
		main_exec_fils(data, env);
	else
		redirect_pere(data, pid);
	return (env);
}
