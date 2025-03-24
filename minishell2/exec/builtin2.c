/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:12:18 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/24 01:09:48 by levaipro         ###   ########.fr       */
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

void	builtin_exit(t_cmd *cmd)
{
	(void)cmd;
	int status;
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
	{
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
	exit(g_exit_code);
}

t_env *builtin_unset(t_env *env, char *unset)
{
	t_env *tmp;
	t_env *head;

	tmp = env;
	head = env;
	if(!unset)
		return(tmp);
	if(ft_strcmp(env->before_eq, unset) == 0)
	{
		// env = env->next;
		free(env->all);
		env->all = NULL;
		env->before_eq = NULL;
		env->after_eq = NULL;
		// env = head;
		env = env->next;
		return(env);
	}
	else
	{
		env = env->next;
		while(env)
		{
			if(ft_strcmp(env->before_eq, unset) == 0)
			{
				free(env->all);
				env->all = NULL;
				env->before_eq = NULL;
				env->after_eq = NULL;
				head->next = env->next;
			}
			env = env->next;
			head = head->next;
		}
	}
	head = tmp;
	return(tmp);
}
