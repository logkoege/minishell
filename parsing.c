#include "minishell.h"

void	parsing(int argc, char **argv)
{
	(void)argv;
	pars_arg(argc);
}

void	pars_arg(int argc)
{
	if (argc != 1)
	{
		printf("Error with number of arg must be 1\n");
		exit(EXIT_SUCCESS);
	}
}
