/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levaipro <levaipro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:44:03 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/28 12:21:30 by levaipro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include "../includes/minishell.h"

void	free_path(t_env *env, char **split)
{
	int i;

	(void)env;
	i = 0;
	if (!split)
		return;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_end(t_env *env, char *p, char **sp, char *pj, char *r)
{
	if (pj)
		free(pj);
	if (r)
		free(r);
	if (p)
		free(p);
	free_path(env, sp);
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
	if (!(p = ft_getenv("PATH", env, 1)) || !(sp = ft_split(p, ':')))
		return (free(p), NULL);
	i = -1;
	while (sp[++i])
	{
		if ((pj = ft_strjoin(sp[i], "/")) && (r = ft_strjoin(pj, cmd))
			&& access(r, F_OK | X_OK) == 0)
			return (free_end(env, p, sp, NULL, NULL), r);
		free(pj);
		free(r);
	}
	return (free_end(env, p, sp, NULL, NULL), NULL);
}

