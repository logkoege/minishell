/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:08:09 by logkoege          #+#    #+#             */
/*   Updated: 2025/02/18 19:11:35 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
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
# include <readline/readline.h>
# include <readline/history.h>

# define WORD		1	// word
# define PIPE		2	// |
# define TRUNC		3	// >
# define INPUT		4	// <
# define APPEND		5	// >>
# define HEREDOC	6	// <<

typedef struct s_env
{
	char			*all;
	char			*before_eq;
	char			*after_eq;
	struct s_env	*next;
}	t_env;

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

typedef struct s_data
{
	t_first	*first;
	t_cmd	*cmd;
	int		pipe[2];
	int		exit_code;
	bool	single_quote;
	bool	double_quote;
	int		j;
	int		i;
}	t_data;

// chain_list.c
t_first	*lstnew(int token, char *ssr);
t_first	*lstlast(t_first *lst);
void	lstadd_back(t_first **lst, t_first *new);

// checker.c
int		check_pipe(char *input, t_data *data);
void	track(int *i, int *j, char *input, char n);
int		check_double_redirect(char *input, t_data *data);
int		check_other(char *input, t_data *data);
int		check_invalid_combinations(char *input, t_data *data);

// free_fonctions.c
void	free_structs(t_data *data);
void	free_all(t_data *data);
void	free_struct(t_data *data);

// spliting.c
char	*start_split(t_data *data, char *input);
char	*delete_space(t_data *data, char *input, int j);

// utils.c
void	rdline(t_data *data, char **envp, t_env *env);
int		ft_strlen(char *str);
void	init_var(t_data *data, int argc, char **argv);
int		is_ws(char c);
int		inputlen(char *input);

// util2.c
int		token_is_valid(char *input, t_data *data);
int		quote_not_closed(t_data *data);
int		skip_quote(char *input, t_data *data);
int		pipe_utils(char *input);

// tokenizer.c
int		tokenizer(char *str);
int		tokenizer_utils(char *str, char n);
void	setup_tokeniser(t_data *data, char *input);

// signal.c
void	handle_signal(int sig);
void	setup_signals(void);

// dollar.c
void	dollar_parser(t_data *data, t_env *env);
void	dollar_checker(t_first *tmp, t_env *env);
void	dollar_changer(t_first *tmp, int i, t_env *env, bool quote);
t_env	*dollar_cmp(t_first *tmp, t_env *env, int i, bool quote);
void	replace_dollar(t_first *tmp, t_env *tenv2, char *str, int i);

// env.c
t_env	*list_env(char **envp, t_env **env);
t_env	*lst_new_env(char *envp);
void	lstadd_back_env(t_env **lst, t_env *new);
t_env	*lstlast_env(t_env *lst);
void	print_lst_first(t_data *data);

// utils3.c
char	*ft_chr(char *s, int c);
char	*ft_dup(char *s1);
char	*ft_sub(char *s, int start, int len);

#endif