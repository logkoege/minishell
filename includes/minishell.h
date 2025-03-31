/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:44:04 by lloginov          #+#    #+#             */
/*   Updated: 2025/03/31 09:21:24 by logkoege         ###   ########.fr       */
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

extern int	g_exit_code;

typedef struct s_env
{
	char			*all;
	char			*before_eq;
	char			*after_eq;
	bool			equal;
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
	bool			infile;
	bool			outfile;
	int				fd_infile;
	int				fd_outfile;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data
{
	t_first	*first;
	t_cmd	*cmd;
	t_env	*env;
	int		pipe[2];
	int		exit_code;
	bool	single_quote;
	bool	double_quote;
	bool	quote;
	int		lst_size;
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
void	free_all(t_data *data, t_env *env);
void	free_struct(t_data *data, t_cmd *cmd);

// spliting.c
int		start_split(t_data *data, char *input);
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
void	signal_heredoc(int sig);

// tokenizer.c
int		tokenizer(char *str);
int		tokenizer_utils(char *str, char n);
void	setup_tokeniser(t_data *data, char *input);

// signal.c
void	handle_signal(int sig);
void	setup_signals(void);

// dollar.c
void	dollar_parser(t_data *data, t_env *env);
void	dollar_checker(t_first *tmp, t_env *env, t_data *data);
int		dollar_changer(t_first *tmp, int i, t_env *env, t_data *data);
t_env	*dollar_cmp(t_first *tmp, t_env *env, int i);
void	replace_dollar(t_first *tmp, t_env *tenv2, char *str, int i);

// dollar2.c
int		remove_dollar(t_first *tmp2, char *str, int i, t_data *data);
char	*ft_itoa(int exit_code);

// env.c
t_env	*list_env(char **envp, t_env **env);
t_env	*lst_new_env(char *envp);
void	lstadd_back_env(t_env **lst, t_env *new);
t_env	*lstlast_env(t_env *lst);
void	print_lst_first(t_data *data);
int		ft_atoi(char *str);

// utils3.c
char	*ft_chr(char *s, int c);
char	*ft_dup(char *s1);
char	*ft_sub(char *s, int start, int len);
char	*ft_dup_digit(char *s1, int dollar);
int		is_digit(char c);

// lst_cmd.c
t_cmd	*lst_new_cmd(t_data *data);
t_cmd	*lstlast_cmd(t_cmd *lst);
t_cmd	*lstadd_back_cmd(t_cmd **lst, t_cmd *new);

// last_chainlist.c
char	*delete_quote(char *str);
t_cmd	*first_to_cmd(t_data *data);
void	print_lst_cmd(t_cmd *cmd);

int					check_path(char *s1,  char *s2);
t_env    			*find_env(t_cmd *exec, char **envp, t_env *env);
char 				*ft_getenv(char *str, t_env *env, int i);


//builtin1
void				builtin_env(t_env *env);
void				builtin_pwd(t_env *env);
void				builtin_echo(t_cmd *exec);
t_env				*bultin_cd(t_env *env, char *dir);
t_env				*builtin_change_pwd(t_env *env, char *old_pwd, char *new_pwd);
void				builtin_home(t_env *env);
t_env 				*builtin_cd_old_pwd(t_env *env);
int 				ft_strcmp_echo(char *s1, char *s2);

//buitlin2
t_env *builtin_unset(t_env *env, char *unset);
void	builtin_exit(t_cmd *cmd);
//innit var
void	innit_var(t_cmd *cmd, t_env *env);

t_env	*builtin_export(t_env *env, t_cmd *cmd);
//export
// t_env 	*buitlin_export(t_env *env, t_cmd *cmd);
int is_builtin(t_data *data, t_env *env);

//export_utils

int	ft_strcmxport(char *s1, char *s2);
char	*malloc_export_eq(char *export, t_env *env);
int	get_export_size(t_env *env);
char	**malloc_export(t_env *env);
int	is_eauql(char *arg);

//export_utils2
void	sort_export(char **export, t_env *env);
void	print_export(char **export);
void	free_export(char **export);
t_env	*unset_export(t_env *env, char *cmd);
int	export_syntax(char *arg, int i);


//error_handling

void    free_exit1(t_cmd *exec, char *pointer, char *msg);
void	free_env(t_env *env);

// // chain lists
// t_env	*list_env(char **envp);
// t_env	*lst_new_env(char *envp);
// void	lstadd_back_env(t_env **lst, t_env *new);
// t_env	*lstlast_env(t_env *lst);

//utils.c
int ft_strlen(char *str);
char				**ft_split(char *s, char c);

//utils2
void ft_fprintf(char *str);
int		ft_strcmp(char *s1, char *s2);
char **env_to_str(t_env *env);

//utils3
int		is_ws(char c);
void	ft_putstr_fd(char *s, int fd);

//join
char	*ft_strjoin(char *s1, char *s2);

//pathfinder
char	*find_path(t_env *env, char *cmd);
void	free_path(t_env *env, char **split);

//exec_minishell
t_env	*main_exec(t_data *data, t_env *env);
t_env *check_arg(t_cmd *cmd, t_env *env);
t_env *exec_1(t_data *data, t_env *env);
t_env	*exec_fils(t_data *data, t_env *env, int *fd_pipe);

//export
int	is_eauql(char *arg);


//infile
int	check_redirect(t_cmd *cmd);

//redirect_exec
void	set_redirects(t_data *data);
void	env_exit(t_data *data);
void	path_error(t_data *data, t_env *env, char **env_s);
void	execve_exit(t_env *env, char *path, char **env_s);
void	redirect_pere(t_data *data, pid_t pid);


//execute pipes

t_env	*exec_solo_builtin(t_data *data, t_env *env);
void	redirect_error(t_data *data, int pipe_fd[2]);
void	create_pipe(t_data *data, int pipe_fd[2]);
void	no_pipe_redirect(t_data *data);
void	waiting_pid(t_cmd *cmd_tmp);


#endif
