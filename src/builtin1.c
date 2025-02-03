/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:06:08 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/03 15:52:04 by lloginov         ###   ########.fr       */
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
	char *pwd;

	// i = 0;
    // while(envp[i])
    // {
    //     if(check_path(envp[i], "PWD=") == 0)
    //     {
	// 		pwd = envp[i] + 4;
    //         printf("%s\n", pwd);
	// 		return;
    //     }
    //     else
    //     	i++;
    // }
	// return;

	(void)envp;
	pwd = getenv("PATH");
	printf("%s\n", pwd);
	return ;
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

void	bultin_cd(t_cmd *exec, char **envp, char *dir)
{
	char *cwd;
	int pwd_size;
	pwd_size = 1024;


	cwd = malloc(sizeof(char *) *pwd_size);
	if(!cwd)
		free_exit1(exec, cwd, "Error : CWD error (1)");

	(void)exec;
	(void)envp;
	dir = "src";
	if(getcwd(cwd, pwd_size) != NULL)
		printf("%s\n", cwd);

	if(chdir(dir) == 0)
	{
		printf("bien cngahge\n");
		if(getcwd(cwd, pwd_size) != NULL)
		{
			printf("voici le nouveau pwd : %s\n", cwd);
			builtin_change_pwd(exec, cwd, pwd_size);
		}
	}
	else
		printf("cd: no such file or directory: %s\n", dir);
	
}

void	builtin_change_pwd(t_cmd *exec, char *cwd, int pwd_size)
{
	char *old_pwd;
	char *new_pwd;

	old_pwd = getenv("PWD");
	new_pwd = getcwd(cwd, pwd_size);
	if(new_pwd == NULL)
		free_exit1(exec, cwd, "Error : getcwd error(1)");
	else
	{
		if(setenv("PWD", old_pwd, 1) == -1)
			free_exit1(exec, cwd, "Error : setenv error (1)");
		printf("NOUVEAU ENV PWD : %s", getenv("PWD"));

	}
}
