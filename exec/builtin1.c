/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:06:08 by lloginov          #+#    #+#             */
/*   Updated: 2025/04/08 14:24:37 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_env *env, t_data *data)

{
	t_env	*head;

	head = env;
	if (!env)
		env_exit(data, env);
	while (head)
	{
		if (head->equal == 1)
			printf("%s\n", head->all);
		head = head->next;
	}
	return ;
}

void	builtin_pwd(t_env *env)
{
	char	*pwd;
	char	buffer[4096];

	(void)env;
	pwd = getcwd(buffer, sizeof(buffer));
	if (pwd)
		printf("%s\n", pwd);
	else
	{
		ft_putstr_fd("bash : pwd : cannot acces current directory\n", 2);
		g_exit_code = 1;
		exit(g_exit_code);
	}
	g_exit_code = 0;
	return ;
}

void	write_echo(t_cmd *exec, int i)
{
	while (exec->arg[i])
	{
		if (ft_strcmp_echo(exec->arg[i], "-n") == 1)
		{
			ft_pustr(exec->arg[i]);
			if (exec->arg[i + 1] != NULL)
				ft_pustr(" ");
		}
		i++;
	}
}

void	builtin_echo(t_cmd *exec)
{
	int	i;
	int	comt;

	comt = 0;
	i = 1;
	if (!exec->arg[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp_echo(exec->arg[1], "-n") == 0)
	{
		i++;
		comt = 1;
	}
	write_echo(exec, i);
	if (comt != 1)
		printf("\n");
	return ;
}
