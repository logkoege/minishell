/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:08:26 by lloginov          #+#    #+#             */
/*   Updated: 2025/04/08 14:19:00 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_inpt(char *input, int pipe_fd[2])
{
	write(pipe_fd[1], input, ft_strlen(input));
	write(pipe_fd[1], "\n", 1);
	free(input);
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
		if (access(outfile, W_OK) != 0 && access(outfile, F_OK) == 0)
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
