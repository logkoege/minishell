#ifndef MNISHELL_H
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

# define CMD		1	// Commande
# define ARG		2	// Argument
# define PIPE		3	// |
# define TRUNC		4	// >
# define INPUT		5	// <
# define APPEND		6	// >>
# define HEREDOC	7	// <<

// typedef struct s_struct
// {

// }	t_struct

// parsing.c
void	parsing(int argc, char **argv);
void	pars_arg(int argc);

// utils.c
void	rdline(void);

#endif