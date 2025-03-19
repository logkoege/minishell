/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:44:03 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/19 23:26:06 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_path(t_env *env, char **split)
{
	int i;

	(void)env;
	i = 0;
	if(!split)
		return;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*find_path(t_env *env, char *cmd)
{
	char *path;
	char **split_path;
	char *pathjoin;
	char *res;
	int i;

	i = 0;
	if(access(cmd, X_OK | F_OK) == 0)
		return(cmd);
	path = ft_getenv("PATH", env, 1);
	split_path = ft_split(path, ':');	
	if(!split_path)
	{
		free(path);
		return(NULL);
	}
	while(split_path[i])
	{
		if(i > 0 && pathjoin)
			free(pathjoin);
		pathjoin = ft_strjoin(split_path[i], "/");
		if (!pathjoin)
		{
			free(path);
			free_path(env, split_path);
			return (NULL);
		}
		res = ft_strjoin(pathjoin, cmd);
		if (!res) 
		{
			free(pathjoin);
			free(path);
			free_path(env, split_path);
			return (NULL);
		}
		if(access(res, F_OK | X_OK) == 0)
		{
			free(path);
			free(pathjoin);
			free_path(env, split_path);
			return(res);
		}
		i++;
		free(pathjoin);
		free(res);
		pathjoin = NULL;
		res = NULL;
	}
	free(pathjoin);
	free(res);
	free(path);
	free_path(env, split_path);
	return(NULL);
}
