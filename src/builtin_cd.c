/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:39:03 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/23 20:48:41 by lloginov         ###   ########.fr       */
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
	while(dir[i])
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

	if(check_dir_cd(dir) == 1)
	{
		printf("bash: cd: too many arguments\n");
		return(env);
	}
	if(!dir)
	{
		chdir(ft_getenv("HOME", env, 3));
		printf("home\n");
		env = builtin_change_pwd(env);

	}
	else if(dir[0] == '-')
	{
		printf("moins aqcui\n");
		env = builtin_cd_old_pwd(env);
	}
	else
	{
		if(chdir(dir) == 0)
			printf("bien cngahge\n");
		else
			printf("cd: no such file or directory: %s\n", dir);
		env = builtin_change_pwd(env);
	}
	env = head;
	return(head);
}
t_env *builtin_cd_old_pwd(t_env *env)
{
	char *old_pwd;
	char *new_pwd;
	t_env *head;
	int k;

	k = 0;
	head = env;
	new_pwd = ft_getenv("PWD", env, 3);
	old_pwd = ft_getenv("OLDPWD", env, 3);
	chdir(old_pwd);
	while (head)
	{
		if (ft_strcmp(head->before_eq, "PWD") == 0)
		{
			free(head->all);
			head->all =	ft_dup(old_pwd);
			head->after_eq = getcwd(NULL, 0);
			k++;
		}
		else if (ft_strcmp(head->before_eq, "OLDPWD") == 0)
		{
			free(head->all);
			head->all =	ft_dup(new_pwd);
			head->after_eq = new_pwd ;
			k++;
		}
		if(k == 2)
			break;
		head = head->next;
	}
	printf("nouveau pwd : %s \n vieux pwd : %s\n", ft_getenv("PWD", env, 1), ft_getenv("OLDPWD", env, 1));
	return(head);
}

t_env	*builtin_change_pwd(t_env *env)
{
	char *old_pwd;
	char *new_pwd;
	t_env *head = env;
	int k;

	k = 0;
	old_pwd = ft_strjoin("OLDPWD=", ft_getenv("PWD", env, 3));
	// printf("old pwd ::::::: %s\n", old_pwd);
	if(!old_pwd)
	{
		fprintf(stderr, "eERRRO\n");
		exit(1);
	}
	new_pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	while (head)
	{
		if (ft_strcmp(head->before_eq, "PWD") == 0)
		{
			free(head->all);
			head->all =	ft_dup(new_pwd);
			head->after_eq = getcwd(NULL, 0);
			free(new_pwd);
			k++;
		}
		else if (ft_strcmp(head->before_eq, "OLDPWD") == 0)
		{
			free(head->all);
			head->all =	ft_dup(old_pwd);
			head->after_eq = old_pwd + 7;
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
		printf("nouveau pwd : %s \n vieux pwd : %s\n", ft_getenv("PWD", env, 1), ft_getenv("OLDPWD", env, 1));
	}
	return(head);
}
