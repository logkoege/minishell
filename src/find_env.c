/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:25:31 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/09 17:50:45 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int check_path(char *s1,  char *s2)
{
    int i;
    
    i = 0;

  while(s2[i])
  {
    if(s1[i] != s2[i])
        return(1);
    else
        i++;
  }
  return(0);
}

// void    read_token(t_cmd *exec)
// {
//     int i;

//     i = 0;


// }

t_env    *find_env(t_cmd *exec, char **envp, t_env *env)
{
	(void)env;
    (void)exec;
	env = list_env(envp);

	// bultin_cd(env, envp, "..");
	find_path(env, "ls");
	return(env);
}

char *ft_getenv(char *str, t_env *env)
{
	t_env *tmp;

	tmp = env;

	if(tmp == NULL)
		printf("ernore\n");
	while(tmp)
	{
		if(ft_strcmp(tmp->before_eq, str) == 0)
		{
			// printf("VOICI : %s\n", tmp->all);
			return(tmp->all);
		}
		tmp = tmp->next;
	}
	return(NULL);
}

