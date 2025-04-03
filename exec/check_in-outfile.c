/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in-outfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:59:44 by lloginov          #+#    #+#             */
/*   Updated: 2025/04/03 14:19:04 by lloginov         ###   ########.fr       */
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
		if (access(infile, R_OK) != 0)
		{
			ft_putstr_fd(" : permission denied\n", 2);
			g_exit_code = 1;
			return (1);
		}
		ft_putstr_fd(" : No such file or directory\n", 2);
		g_exit_code = 1;
		return (1);
	}
	if (cmd->infile)
		close(cmd->fd_infile);
	if (!cmd->arg[0])
		return (1);
	cmd->infile = 1;
	cmd->fd_infile = fd;
	return (0);
}

int	outfiler(t_cmd *cmd, char *outfile)
{
	int	fd;

	if (!outfile)
		return (1);
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(outfile, 2);
		if (access(outfile, W_OK) != 0)
		{
			ft_putstr_fd(" : permission denied\n", 2);
			g_exit_code = 1;
			return (1);
		}
		ft_putstr_fd(" : No such file or directory\n", 2);
		g_exit_code = 1;
		return (1);
	}
	if (cmd->outfile)
		close(cmd->fd_outfile);
	cmd->outfile = 1;
	if (!cmd->arg[0])
		return (1);
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
		if (access(file, W_OK) != 0)
		{
			ft_putstr_fd(" : permission denied\n", 2);
			g_exit_code = 1;
			return (1);
		}
		ft_putstr_fd(" : No such file or directory\n", 2);
		g_exit_code = 1;
		return (1);
	}
	if (cmd->outfile)
		close(cmd->fd_outfile);
	if (!cmd->arg[0])
		return (1);
	cmd->outfile = 1;
	cmd->fd_outfile = fd;
	return (0);
}

int	redirect2(t_cmd *cmd, int i, int j)
{
	if (cmd->tkn[i] == INPUT)
	{
		if (infiler(cmd, cmd->file[j]) == 1)
			return (-424242);
		j++;
	}
	else if (cmd->tkn[i] == TRUNC)
	{
		if (outfiler(cmd, cmd->file[j]) == 1)
			return (-424242);
		j++;
	}
	else if (cmd->tkn[i] == APPEND)
	{
		if (appender(cmd, cmd->file[j]) == 1)
			return (-424242);
		j++;
	}
	else if (cmd->tkn[i] == HEREDOC)
	{
		if (here_doocker(cmd, cmd->file[j]) == 1)
			return (-424242);
		j++;
	}
	return (j);
}

int	check_redirect(t_cmd *cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (cmd->tkn[i])
	{
		j = redirect2(cmd, i, j);
		if (j < 0)
		{
			if (g_exit_code != 130)
				g_exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
