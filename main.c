#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	parsing(argc, argv);
	rdline();
	return (0);
}