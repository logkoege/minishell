/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in-outfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:59:44 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/26 21:43:09 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	infiler(t_cmd *cmd, char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(infile, 2);
		ft_putstr_fd(" : No such file or directory", 2);
		g_exit_code = 1;
		return (1);
	}
	if (cmd->infile)
		close(cmd->fd_infile);
	cmd->infile = 1;
	cmd->fd_infile = fd;
	return (0);
}
int	outfiler(t_cmd *cmd, char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(outfile, 2);
		ft_putstr_fd(" : No such file or directory", 2);
		g_exit_code = 1;
		return (1);
	}
	if (cmd->outfile)
		close(cmd->fd_outfile);
	cmd->outfile = 1;
	cmd->fd_outfile = fd;
	return (0);
}

int	appender(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" : No such file or directory", 2);
		g_exit_code = 1;
		return (1);
	}
	if (cmd->outfile)
		close(cmd->fd_outfile);
	cmd->outfile = 1;
	cmd->fd_outfile = fd;
	return (0);
}

int	here_doocker(t_cmd *cmd, char *herdoc)
{
	int		pipe_fd[2];
	char	*input;
	int		fd;

	fd = dup(0);
	(void)cmd;
	(void)herdoc;
	signal(SIGINT, signal_heredoc);

	if(pipe(pipe_fd) == -1)
	{
		
		ft_putstr_fd("Pipe heredoc error\n", 2);
		g_exit_code = 1;
		return(1);
	}
	while(1)
	{
		input = readline(">");
		if (input == NULL && g_exit_code == 99)
		{
			dup2(fd, 0);
			g_exit_code = 130;
			signal(SIGINT, handle_signal);
			break;
		}
		if(input == NULL)
			continue;
		if(ft_strcmp(input, herdoc) == 0
			&& ft_strlen(input) > 0)
			break;
		write(pipe_fd[1], input, ft_strlen(input));
		write(pipe_fd[1], "\n", 1);

	}
	close(pipe_fd[1]);
	if(cmd->infile)
		close(cmd->fd_infile);
	cmd->infile = 1;
	cmd->fd_infile = pipe_fd[0];
	return(0);
}

int	check_redirect(t_cmd *cmd)
{
	int i;
	int j;

	j = 0;
	i = 0;

	// while(cmd)
	// {
		while(cmd->tkn[i])
		{
			if(cmd->tkn[i] == INPUT)
			{
				if(infiler(cmd, cmd->file[j]) == 1)
					return(1);
				j++;
			}
			else if(cmd->tkn[i] == TRUNC)
			{
				if(outfiler(cmd, cmd->file[j]) == 1)
						return(1);
				j++;
			}
			else if(cmd->tkn[i] == APPEND)
			{
				if(appender(cmd, cmd->file[j]) == 1)
					return(1);
				j++;
			}
			else if(cmd->tkn[i] == HEREDOC)
			{
				if(here_doocker(cmd, cmd->file[j]) == 1)
					return(1);
				j++;
			}
			

			i++;
		}
		// cmd = cmd->next;
	// }
	return(0);
}

// void	redirect(t_data *data, int fd_in, int fd_out)
// {

// 	dup2(fd_in, STDIN_FILENO);
// 	dup2(fd_out, STDOUT_FILENO);
// }