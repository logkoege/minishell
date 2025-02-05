/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:25:31 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/05 18:29:18 by lloginov         ###   ########.fr       */
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

char    *find_env(t_cmd *exec, char **envp, t_env *env)
{
	(void)env;
    (void)exec;
    list_env(envp);

	return(NULL);
}

