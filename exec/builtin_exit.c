/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:53:15 by levaipro          #+#    #+#             */
/*   Updated: 2025/03/28 12:05:01 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exit_check(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] != '-' && str[i] != '+' && is_digit(str[i]) != 1)
			return(1);
		i++;
    }
	return(0);
}

void    exit2(t_cmd *cmd)
{
    int status;
   
	status = ft_atoi(cmd->arg[1]);
	if(exit_check(cmd->arg[1]) == 1)
	{
		write(2, "exit : numeric argument required\n", ft_strlen("exit : numeric argument required\n"));
		g_exit_code = 2;
		exit(g_exit_code);
	}
	else
		g_exit_code = status;
}


void	builtin_exit(t_cmd *cmd)
{
	(void)cmd;
	int i;

	i = 0;
	while(cmd->arg[i])
		i++;
	if(i > 2)
	{
		write(2, "exit : too many arguments\n", ft_strlen("exit : too many arguments\n"));
		g_exit_code = 1;
		exit(g_exit_code);
	}
	if(cmd->arg[1] == NULL)
		exit(g_exit_code);
	else
        exit2(cmd);
	exit(g_exit_code);
}
