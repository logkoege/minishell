/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:44:59 by lloginov          #+#    #+#             */
/*   Updated: 2025/01/29 14:11:14 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd exec;
	(void)ac;
	(void)av;
	(void)envp;
	find_env(exec, envp);
	// while (1)
	// {

	// }
	return(0);
}
