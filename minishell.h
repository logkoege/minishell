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

# define word		1	// word
# define PIPE		2	// |
# define TRUNC		3	// >
# define INPUT		4	// <
# define APPEND		5	// >>
# define HEREDOC	6	// <<

typedef struct s_token
{
	int		type;
	char	*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char	**arg;
	bool	skip_cmd;
	t_token	*token;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_token	*token;
	t_cmd	*cmd;
	int		pipe[2];
	int		exit_code;
	bool	single_quote;
	bool	double_quote;
}	t_data;

// main.c
int		main(int argc, char **argv, char **envp);

// free_fonctions.c
void	free_structs(t_data *data);
void	free_all(t_data *data);

// spliting.c
char	*start_split(t_data *data, char *input);
char	*delete_space(t_data *data, char *input);

// utils.c
void	rdline(t_data *data);
int		ft_strlen(char *str);
void	init_var(t_data *data, int argc, char **argv);

#endif