/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:22:32 by levaipro          #+#    #+#             */
/*   Updated: 2025/03/31 09:19:27 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*exec_solo_builtin(t_data *data, t_env *env)
{
	if (check_redirect(data->cmd) == 1)
	{
		g_exit_code = 1;
		return (env);
	}
	if (data->cmd->infile == 1)
	{
		dup2(data->cmd->fd_infile, STDIN_FILENO);
		close(data->cmd->fd_infile);
	}
	else if (data->cmd->outfile == 1)
	{
		dup2(data->cmd->fd_outfile, STDOUT_FILENO);
		close(data->cmd->fd_outfile);
	}
	env = check_arg(data->cmd, env);
	return (env);
}

void	redirect_error(t_data *data, int pipe_fd[2])
{
	if (data->cmd->next)
	{
		g_exit_code = 1;
		if (pipe(pipe_fd) == -1)
		{
			printf("Error : pipe\n");
			exit(1);
		}
		data->cmd->next->fd_infile = pipe_fd[0];
		data->cmd->fd_outfile = pipe_fd[1];
		close(pipe_fd[1]);
	}
}

void	create_pipe(t_data *data, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		printf("Error : pipe\n");
		exit(1);
	}
	data->cmd->next->fd_infile = pipe_fd[0];
	if (data->cmd->outfile == 1)
		close(pipe_fd[1]);
	else
		data->cmd->fd_outfile = pipe_fd[1];
}

void	sinal_shell(int signal)
{
	if (signal == SIGINT)
		ft_putstr_fd("", 1);
}

void	waiting_pid(t_cmd *cmd_tmp)
{
	int	status;
	//signal(SIGINT, &sinal_shell);
	while (cmd_tmp)
	{
		if (waitpid(cmd_tmp->pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
				g_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_code = 128 + WTERMSIG(status);
		}
		cmd_tmp = cmd_tmp->next;
	}
}