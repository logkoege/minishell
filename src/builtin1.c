/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:06:08 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/12 15:00:55 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_env *env)
{
	t_env *head;

	head = env;

	while(head)
	{
		printf("%s\n", head->all);
		head = head->next;
	}
}

void	builtin_pwd(t_env *env)
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
	// retrn;

	pwd = ft_getenv("PATH", env);
	printf("%s\n", pwd);
	return ;
}

void	builtin_echo(t_cmd *exec, int nb)
{

	int i;
	int j;
	t_cmd *head;

	j = 1;
	i = 0;
	while(exec->tkn[0] == 1)
	{
		exec = exec->next;
	}
	if(nb == 1)
	while(head != exec)
	{
		// printf("%s\n", head->arg);
		head = head->next;
	}
	
}

void	bultin_cd(t_env *env, char *dir)
{
	char *cwd;
	int pwd_size;
	pwd_size = 1024;


	cwd = malloc(sizeof(char *) * pwd_size);
	if(!cwd)
		free_exit1(env, cwd, "Error : CWD error (1)");
	// dir = "src";
	printf("\n%s\n", env->all);
	// if(getcwd(cwd, pwd_size) != NULL)
	// 	printf("%s\n", cwd);
	if(chdir(dir) == 0)
	{
		printf("bien cngahge\n");
		if(getcwd(cwd, pwd_size) != NULL)
		{
			// printf("voici le nouveau pwd : %s\n", cwd);
			builtin_change_pwd(env, cwd, pwd_size);
		}
	}
	else
		printf("cd: no such file or directory: %s\n", dir);
	
}

void	builtin_change_pwd(t_env *env, char *cwd, int pwd_size)
{
	char *old_pwd;
	char *new_pwd;
	(void)old_pwd;
	t_env *head = env;
	old_pwd = ft_getenv("PWD", env);
	if(!old_pwd)
	{
		fprintf(stderr, "eERRRO\n");
		exit(1);
	}
	new_pwd = ft_strjoin("PWD=", getcwd(cwd, pwd_size));
	// printf("old pwd : %s\n new pwd %s\n", old_pwd, new_pwd);
	while (head)
	{
		if (ft_strcmp(head->before_eq, "PWD") == 0)
		{
			free(head->all);
			head->all =	ft_dup(new_pwd);
			break;
		}
		head = head->next;
	}
	if(new_pwd == NULL)
		printf("wrong\n");	
	// free_exit1(exec, cwd, "Error : getcwd error(1)");
	else
	{
		printf("NOUVEAU head PWD : %s\n", ft_getenv("PWD", head));
	}
	while(head)
	{
		printf("%s\n", head->all);
		head = head->next;
	}
	return;
}
