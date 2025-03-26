/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:44:03 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/25 13:15:40 by levaipro         ###   ########.fr       */
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
		if(split[i])
			free(split[i]);
		i++;
	}
	if(split)
		free(split);
}

char	*find_path(t_env *env, char *cmd)
{
	char *path;
	char **split_path;
	char *pathjoin;
	char *res;
	int i;
	
	if(!cmd)
		return(NULL);
	i = 0;
	if(access(cmd, X_OK | F_OK) == 0)
		return(cmd);
	path = ft_getenv("PATH", env, 1);
	if(!path)
		return(NULL);
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
			if(pathjoin)
				free(pathjoin);
			if(path)
				free(path);
			free_path(env, split_path);
			return (NULL);
		}
		if(access(res, F_OK | X_OK) == 0)
		{
			// if(path)
				// free(path);
			if(pathjoin)
				free(pathjoin);
			free_path(env, split_path);
			return(res);
		}
		i++;
		if(pathjoin)
			free(pathjoin);
		if(res)
			free(res);
		pathjoin = NULL;
		res = NULL;
	}
	if(pathjoin)
		free(pathjoin);
	if(res)
		free(res);
	if(path)
		free(path);
	free_path(env, split_path);
	return(NULL);
}
