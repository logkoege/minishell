/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:11:21 by logkoege          #+#    #+#             */
/*   Updated: 2025/03/07 17:09:46 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_env		*env;

	data.first = NULL;
	env = NULL;
	setup_signals();
	init_var(&data, argc, argv);
	rdline(&data, envp, env);
	//exec ici
	free_all(&data);
	return (0);
}
