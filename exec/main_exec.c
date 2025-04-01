/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:50:06 by levaipro          #+#    #+#             */
/*   Updated: 2025/03/31 08:54:26 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	no_pipe_redirect(t_data *data)
{
	if (data->cmd->outfile != 1)
		data->cmd->fd_outfile = STDOUT_FILENO;
	if (data->cmd->infile != 1 && !data->cmd->prev)
		data->cmd->fd_infile = STDIN_FILENO;
}

void	pipe_info(t_data *data, int pipe_fd[2])
{
	if (data->cmd->next)
		create_pipe(data, pipe_fd);
	else
		no_pipe_redirect(data);
}

t_env	*exec_1(t_data *data, t_env *env)
{
	int		pipe_fd[2];
	t_cmd	*cmd_tmp;

	cmd_tmp = data->cmd;
	while (data->cmd)
	{
		if (!data->cmd->arg[0] && !data->cmd->file[0])
		{
			data->cmd = data->cmd->next;
			continue ;
		}
		if (!data->cmd->next && !data->cmd->prev && is_builtin(data, env))
			return (exec_solo_builtin(data, env));
		if (check_redirect(data->cmd) == 1)
		{
			redirect_error(data, pipe_fd);
			data->cmd = data->cmd->next;
			continue ;
		}
		pipe_info(data, pipe_fd);
		env = exec_fils(data, env, pipe_fd);
		data->cmd = data->cmd->next;
	}
	waiting_pid(cmd_tmp);

	return (env);
}
