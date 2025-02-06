/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:44:59 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/06 18:42:33 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd exec;
	t_env env;
	(void)ac;
	(void)av;
	(void)envp;

	find_env(&exec, envp, &env);
	
	// builtin_env(envp);
	// builtin_echo(&exec, 1);
	bultin_cd(&env, envp, "cd ..");
	// builtin_pwd(envp);
	// while (1)
	// {

	// }
	return(0);
}
