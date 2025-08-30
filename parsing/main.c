/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:11:21 by logkoege          #+#    #+#             */
/*   Updated: 2025/04/03 17:01:20 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_env		*env;

	data.first = NULL;
	env = NULL;
	g_exit_code = 0;
	setup_signals();
	init_var(&data, argc, argv);
	env = list_env(envp, &env);
	rdline(&data, envp, env);
	free_all(&data, env, 1);
	return (g_exit_code);
}
