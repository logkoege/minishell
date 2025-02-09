/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:44:04 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/09 17:50:11 by lloginov         ###   ########.fr       */
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

typedef struct s_env
{
	char			*all;
	char			*before_eq;
	char			*after_eq;
	struct s_env	*next;
}	t_env;

int					check_path(char *s1,  char *s2);
t_env    			*find_env(t_cmd *exec, char **envp, t_env *env);
char 				*ft_getenv(char *str, t_env *env);

//builtin1
void				builtin_env(char **envp);
void				builtin_pwd(t_env *env);
void				builtin_echo(t_cmd *exec, int nb);
void				bultin_cd(t_env *env, char **envp, char *dir);
void				builtin_change_pwd(t_env *env, char *cwd, int pwd_size);

//innit var
void	innit_var(t_cmd *cmd, t_env *env);

//error_handling

void    free_exit1(t_cmd *exec, char *pointer, char *msg);

// chain lists
t_env	*list_env(char **envp);
t_env	*lst_new_env(char *envp);
void	lstadd_back_env(t_env **lst, t_env *new);
t_env	*lstlast_env(t_env *lst);


//utils.c
int ft_strlen(char *str);
char				**ft_split(char *s, char c);

//utils2
char	*ft_dup(char *s1);
char	*ft_chr(char *s, int c);
char	*ft_sub(char *s, int start, int len);
int		ft_strcmp(char *s1, char *s2);

//join
char	*ft_strjoin(char *s1, char *s2);

//pathfinder
char	*find_path(t_env *env, char *cmd);

//exec_minishell
void	main_exec(t_cmd *exec, t_env *env, char **envp);


#endif