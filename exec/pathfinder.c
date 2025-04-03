/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:44:03 by lloginov          #+#    #+#             */
/*   Updated: 2025/04/03 17:19:02 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include "../includes/minishell.h"

void	free_path(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_end(char *p, char **sp, char *pj, char *r)
{
	if (pj)
		free(pj);
	if (r)
		free(r);
	if (p)
		free(p);
	free_path(sp);
}

char	*find_path(t_env *env, char *cmd)
{
	char	*p;
	char	**sp;
	char	*pj;
	char	*r;
	int		i;

	if (!cmd || access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	p = ft_dup(ft_getenv("PATH", env, 1));
	if (!p)
		return (NULL);
	sp = ft_split (p, ':');
	if (!sp)
		return (free(p), NULL);
	i = -1;
	while (sp[++i])
	{
		pj = ft_strjoin(sp[i], "/");
		r = ft_strjoin(pj, cmd);
		if (access(r, F_OK | X_OK) == 0)
			return (free_end(p, sp, NULL, NULL), r);
		free(pj);
		free(r);
	}
	return (free_end(p, sp, NULL, NULL), NULL);
}
