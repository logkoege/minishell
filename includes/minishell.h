/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:44:04 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/03 16:07:19 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <signal.h>
# include <errno.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>

# define WORD		1	// word
# define PIPE		2	// |
# define TRUNC		3	// >
# define INPUT		4	// <
# define APPEND		5	// >>
# define HEREDOC	6	// <<

typedef struct s_first
{
	int				token;
	char			*str;
	struct s_first	*next;
}	t_first;

typedef struct s_cmd
{
	char			**arg;
	bool			skip_cmd;
	char			**file;
	int				*tkn;
	t_first			*first;
	struct s_cmd	*next;
}	t_cmd;

typedef	struct s_env
{
	char			**envi;
	int				i;
	struct s_env	*next;
}	t_env;


int					check_path(char *s1,  char *s2);
char    			*find_env(t_cmd *exec, char **envp);
char				**ft_split(char *s, char c);

//builtin1
void				builtin_env(char **envp);
void				builtin_pwd(char **envp);
void				builtin_echo(t_cmd *exec, int nb);
void				bultin_cd(t_cmd *exec, char **envp, char *dir);
void				builtin_change_pwd(t_cmd *exec, char *cwd, int pwd_size);


//error_handling

void    free_exit1(t_cmd *exec, char *pointer, char *msg);




#endif