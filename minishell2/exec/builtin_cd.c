/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:39:03 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/28 14:09:41 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *cd_home(t_env *env)
{
	char *pwd;
	char *old_pwd;

	pwd = ft_getenv("HOME", env, 3);
	if(!pwd)
	{
		g_exit_code = 1;
		perror("bash: cd: HOME not set\n");
		return(env);
	}
	if(chdir(pwd) == 0)
	old_pwd = ft_dup(ft_getenv("PWD", env, 3));
	pwd = ft_dup(ft_getenv("HOME", env, 3));
	env = builtin_change_pwd(env, old_pwd, pwd);
	return(env);
}

t_env *cd_old_pwd(t_env *env)
{
	char *old_pwd;
	char  *pwd;
	old_pwd = ft_getenv("OLDPWD", env, 3);
	if(!old_pwd)
	{
		g_exit_code = 1;
		perror("bash: cd: OLDPWD not set\n");
		return(env);
	}
	chdir(old_pwd);
	old_pwd = ft_dup(ft_getenv("PWD", env, 3));
	pwd = ft_dup(ft_getenv("OLDPWD", env, 3));
	env = builtin_change_pwd(env, old_pwd, pwd);
	return(env);
}

t_env	*bultin_cd(t_env *env, char *dir)
{
	t_env *head;
	head = env;
	char *pwd;
	char *old_pwd;
	char buffer[4096];

	if(!dir)
		env = cd_home(env);
	else if(dir[0] == '-')
		env = cd_old_pwd(env);
	else
	{
		if(chdir(dir) != 0)
		{
			g_exit_code = 1;
			perror("bash : cd ");
			return(env);
		}
		pwd = ft_dup(getcwd(buffer, sizeof(buffer)));
		old_pwd = ft_dup(ft_getenv("PWD", env, 3));
		env = builtin_change_pwd(env, old_pwd, pwd);
	}
	env = head;
	return(head);
}
int old_pwd_s(t_env *head, int k, char *old_pwd)
{
	free(head->all);
	head->all = NULL;
	head->all =	ft_strjoin("OLDPWD=", old_pwd);
	free(head->after_eq);
	head->after_eq = ft_dup(old_pwd);
	return(k++);
}

t_env	*builtin_change_pwd(t_env *env, char *old_pwd, char *new_pwd)
{
	t_env *head;

	head = env;
	int k;
	k = 0;
	while (head)
	{
		if (ft_strcmp(head->before_eq, "PWD") == 0)
		{
			free(head->all);
			head->all =	ft_strjoin("PWD=", new_pwd);
			free(head->after_eq);
			head->after_eq = ft_dup(new_pwd);
			k++;
		}
		else if (ft_strcmp(head->before_eq, "OLDPWD") == 0)
			k+= old_pwd_s(head, k, old_pwd);
		if(k == 2)
			break;
		head = head->next;
	}
	free(old_pwd);
	free(new_pwd);
	return(env);
}
