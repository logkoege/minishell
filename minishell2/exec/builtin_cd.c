/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:39:03 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/10 15:55:04 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dir_cd(char *dir)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if(!dir)
		return(0);
	while(dir[i] && dir[i-1] == '\\')
	{
		if(is_ws(dir[i]) == 1)
			k = 1;
		else if(is_ws(dir[i]) != 1 && k == 1)
			return(1);
		i++;
	}
	return(0);
}

t_env	*bultin_cd(t_env *env, char *dir)
{
	t_env *head;
	head = env;
	char *pwd;
	char *old_pwd;

	if(check_dir_cd(dir) == 1)
	{
		printf("bash: cd: too many arguments\n");
		return(env);
	}
	if(!dir)
	{
		pwd = ft_getenv("HOME", env, 3);
		if(!pwd)
		{
			printf("bash: cd: HOME not set\n");
			return(env);
		}
		if(chdir(pwd) == 0)
		old_pwd = ft_getenv("PWD", env, 3);
		env = builtin_change_pwd(env, old_pwd, ft_getenv("HOME", env, 3));
	}
	else if(dir[0] == '-')
	{
		old_pwd = ft_getenv("OLDPWD", env, 3);
		if(!old_pwd)
		{
			printf("bash: cd: OLDPWD not set\n");
			return(env);
		}
		if(chdir(old_pwd) == 0)
			printf("bien cngahge - \n");
		env = builtin_change_pwd(env, ft_getenv("PWD", env, 3), ft_getenv("OLDPWD", env, 3));
	}
	else
	{
		if(chdir(dir) == 0)
			printf("bien cngahge\n");
		else
			printf("cd: no such file or directory: %s\n", dir);
		env = builtin_change_pwd(env, ft_getenv("PWD", env, 3), getcwd(NULL, 0));
	}
	env = head;
	return(head);
}

t_env	*builtin_change_pwd(t_env *env, char *old_pwd, char *new_pwd)
{
	t_env *head = env;
	int k;

	k = 0;
	if(!old_pwd)
	{
		fprintf(stderr, "eERRRO\n");
		exit(1);
	}
	while (head)
	{
		if (ft_strcmp(head->before_eq, "PWD") == 0)
		{
			free(head->all);
			head->all =	ft_strjoin("PWD=", new_pwd);
			head->after_eq = new_pwd;
			k++;
		}
		else if (ft_strcmp(head->before_eq, "OLDPWD") == 0)
		{
			free(head->all);
			head->all =	ft_strjoin("OLDPWD=", old_pwd);
			head->after_eq = old_pwd;
			k++;
		}
		if(k == 2)
			break;
		head = head->next;
	}
	if(new_pwd == NULL)
		printf("wrong\n");
	else
	{
		// printf("NOUVEAU head PWD : %s\n", ft_getenv("PWD", head));
		printf("pwd changed\n");
		// printf("nouveau pwd : %s \n vieux pwd : %s\n", ft_getenv("PWD", env, 1), ft_getenv("OLDPWD", env, 1));
	}
	return(head);
}
