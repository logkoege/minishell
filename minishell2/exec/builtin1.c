/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:06:08 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/21 14:52:32 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_env *env)
{
	t_env *head;

	head = env;

	while(head)
	{
		if(head->equal == 1)
			printf("%s\n", head->all);
		head = head->next;
	}
	exit(EXIT_SUCCESS);
}

void	builtin_pwd(t_env *env)
{
	char *pwd;
	(void)env;
	char buffer[4096];

	pwd = getcwd(buffer, sizeof(buffer));
	if(pwd)
		printf("%s\n", pwd);
	else
	{
		printf("PWD error \n");
		exit(EXIT_FAILURE);
	}
	exit(1);
}

void	builtin_echo(t_cmd *exec)
{

	// t_cmd *head;
	int i;
	int comt;

	comt = 0;
	i = 1;
	if(!exec->arg[1])
	{
		printf("\n");
		return;
	}
	if(ft_strcmp_echo(exec->arg[1], "-n") == 0)
	{
		i++;
		comt = 1;
	}
	while(exec->tkn[i] == 1)
	{
		printf("%s", exec->arg[i]);
		if(exec->arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if(comt != 1)
		printf("\n");
	exit(EXIT_SUCCESS);
}
