/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:25:31 by lloginov          #+#    #+#             */
/*   Updated: 2025/01/31 19:56:05 by lloginov         ###   ########.fr       */
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

char    *find_env(t_cmd *exec, char **envp)
{
    int i;

    char *path;
    char **execut;
    (void)path;
    (void)exec;
    (void)execut;
	(void)envp;

    i = 0;
	i++;
    // while(envp[i])
    // {
    //     if(check_path(envp[i], "PATH=") == 0)
    //     {
    //         path = envp[i] + 5;
    //         execut = ft_split(path, ':');
    //     }
    //     else
    //     {
    //         i++;
    //     }
    // }
    return(NULL);
}

