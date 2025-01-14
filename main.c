#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	(void)envp;
	init_var(&data, argc, argv);
	rdline(&data);
	free_all(&data);
	return (0);
}