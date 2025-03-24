/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:11:21 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/24 17:32:33 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_code;

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
	free_all(&data);
	return (g_exit_code);
}
