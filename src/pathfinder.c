/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:44:03 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/09 17:40:33 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(t_env *env, char *cmd)
{
	char *path;
	char **split_path;
	char *pathjoin;
	char *res;
	int i;

	i = 0;
	path = ft_getenv("PATH", env);
	split_path = ft_split(path, ':');	
	while(split_path[i])
	{
		pathjoin = ft_strjoin(split_path[i], "/");
		res = ft_strjoin(pathjoin, cmd);
		if(access(res, F_OK | X_OK) == 0)
		{
			printf("path = %s", res);
			// free(pathjoin);
			// free(split_path);
			return(res);
		}
		i++;
	}
	return(NULL);
}
