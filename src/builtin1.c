/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:06:08 by lloginov          #+#    #+#             */
/*   Updated: 2025/01/31 20:11:41 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(char **envp)
{
	int i;

	i = 0;

	if(!envp)
		return ;
	while(envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	builtin_pwd(char **envp)
{
	int i;
	char *pwd;

	i = 0;
    while(envp[i])
    {
        if(check_path(envp[i], "PWD=") == 0)
        {
			pwd = envp[i] + 4;
            printf("%s\n", pwd);
			return;
        }
        else
        	i++;
    }
	return;
}

void	builtin_echo(t_cmd *exec, int nb)
{
    // exec->arg = (char **)malloc(4 * sizeof(char *));
	// exec->tkn = (int *)malloc(4 * sizeof(int)); 
	
	// exec->arg[0] = "bonjour ";
	// exec->arg[1] = "bonjour1 ";
	// exec->arg[2] = "bonjour2 ";
	// exec->arg[3] = "bonjour3 ";
	// exec->tkn[0] = 1;
	// exec->tkn[1] = 1;
	// exec->tkn[2] = 1;
	// exec->tkn[3] = 1;
	int i;
	int j;

	j = 1;
	i = 0;
	while(exec->tkn[i] == 1)
		i++;
	if(nb == 0)
	{
		while(i > j)
		{
			printf("%s", exec->arg[j]);
			j++;
		}
		printf("\n");
	}
	else if(nb == 1)
	{
		while(i > j)
		{
			printf("%s", exec->arg[j]);
			j++;
		}
	}
}
