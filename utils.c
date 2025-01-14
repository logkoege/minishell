#include "minishell.h"
void	rdline(void)
{
	char *inpt;

	while (1)
	{
		inpt = readline("minishell$ ");
		add_history(inpt);
		printf("%s\n", inpt);
	}
}