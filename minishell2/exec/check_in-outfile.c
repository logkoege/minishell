/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in-outfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:59:44 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/17 15:40:37 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	infiler(t_cmd *cmd, char *infile)
{
	int fd;

	fd = open(infile, O_RDONLY);
	if(fd == -1)
	{
		printf("bash: %s: No such file or directory\n", infile);
		exit(1);
	}

	cmd->fd_infile = fd;
	return(0);
}
int outfiler(t_cmd *cmd, char *outfile)
{
	int fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1)
	{
		printf("bash: %s: No such file or directory\n", outfile);
		return(1);
	}
	cmd->fd_outfile = fd;
	return(0);
}

void	check_redirect(t_cmd *cmd)
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
				infiler(cmd, cmd->file[j]);
				j++;
			}
			else if(cmd->tkn[i] == TRUNC)
			{
				outfiler(cmd, cmd->file[j]);
				j++;
			}
			// else if(cmd->tkn[i] == APPEND)
				// outfiler(cmd, cmd->file[i]);
			

			i++;
		}
		// cmd = cmd->next;
	// }
	return;
}

// void	redirect(t_data *data, int fd_in, int fd_out)
// {

// 	dup2(fd_in, STDIN_FILENO);
// 	dup2(fd_out, STDOUT_FILENO);
// }