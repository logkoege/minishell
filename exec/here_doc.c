/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:18:28 by lloginov          #+#    #+#             */
/*   Updated: 2025/04/03 14:17:01 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	here_doc_cmp(char *input, char *herdoc)
{
	if (ft_strcmxport(input, herdoc) == 0 && ft_strlen(input) > 0)
		return (1);
	return (0);
}

int	end_heredoc(char *input, int pipe_fd[2], t_cmd *cmd)
{
	free(input);
	close(pipe_fd[1]);
	if (cmd->infile)
		close(cmd->fd_infile);
	cmd->infile = 1;
	cmd->fd_infile = pipe_fd[0];
	if (g_exit_code == 130)
	{
		return (1);
	}
	if (!cmd->arg[0])
		return (1);
	return (0);
}

int	pipe_error(int status)
{
	ft_putstr_fd("Pipe heredoc error\n", 2);
	g_exit_code = status;
	return (1);
}

void	free_inpt(char *input, int pipe_fd[2])
{
	write(pipe_fd[1], input, ft_strlen(input));
	write(pipe_fd[1], "\n", 1);
	free(input);
}

int	here_doocker(t_cmd *cmd, char *herdoc)
{
	int		pipe_fd[2];
	char	*input;
	int		fd;

	fd = dup(0);
	signal(SIGINT, signal_heredoc);
	if (pipe(pipe_fd) == -1)
		return (pipe_error(1));
	while (1)
	{
		input = readline(">");
		if (input == NULL && g_exit_code == 99)
		{
			dup2(fd, 0);
			g_exit_code = 130;
			signal(SIGINT, &signal_heredoc);
			break ;
		}
		if (input == NULL && print_heredoc_d(herdoc))
			break ;
		if (here_doc_cmp(input, herdoc) == 1)
			break ;
		free_inpt(input, pipe_fd);
	}
	return (end_heredoc(input, pipe_fd, cmd));
}
