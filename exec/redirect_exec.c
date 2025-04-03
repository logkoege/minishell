/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:20:11 by levaipro          #+#    #+#             */
/*   Updated: 2025/04/03 15:23:24 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_redirects(t_data *data)
{
	if (data->cmd->next)
	{
		dup2(data->cmd->fd_outfile, STDOUT_FILENO);
		close(data->cmd->fd_outfile);
		close(data->cmd->next->fd_infile);
	}
	if (data->cmd->prev)
	{
		dup2(data->cmd->fd_infile, STDIN_FILENO);
		close(data->cmd->fd_infile);
	}
	if (data->cmd->infile == 1)
	{
		dup2(data->cmd->fd_infile, STDIN_FILENO);
		close(data->cmd->fd_infile);
	}
	else if (data->cmd->outfile == 1)
	{
		dup2(data->cmd->fd_outfile, STDOUT_FILENO);
		printf("YES %d\n", data->cmd->fd_outfile);
		close(data->cmd->fd_outfile);
	}
}

void	env_exit(t_data *data)
{
	close(data->cmd->fd_infile);
	close(data->cmd->fd_outfile);
	exit(g_exit_code);
}

void	path_error(t_data *data, char **env_s)
{
	ft_putstr_fd(data->cmd->arg[0], 2);
	ft_putstr_fd(" : command not found\n", 2);
	free_path(env_s);
	g_exit_code = 127;
	exit(g_exit_code);
}

void	execve_exit(char *path, char **env_s)
{
	if (path)
		free(path);
	free_path(env_s);
	printf("execve error \n");
	g_exit_code = 126;
	exit(g_exit_code);
}

void	redirect_daddy(t_data *data, pid_t pid)
{
	if (data->cmd->fd_infile != STDIN_FILENO
		&& data->cmd->fd_infile != -4242)
		close(data->cmd->fd_infile);
	if (data->cmd->fd_outfile != STDOUT_FILENO
		&& data->cmd->fd_outfile != -4242)
		close(data->cmd->fd_outfile);
	data->cmd->pid = pid;
}
