/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:11:21 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/11 17:08:01 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_env		*env;

	data.first = NULL;
	env = NULL;
	setup_signals();
	init_var(&data, argc, argv);
	rdline(&data, envp, env);
	free_all(&data);
	return (0);
}
