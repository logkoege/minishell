#include "minishell.h"

void	rdline(t_data *data)
{
	char *inpt;
	while (1)
	{
		inpt = readline("minishell$ ");
		if (!inpt || inpt[0] == '\0')
			continue ;
		start_split(data, inpt);
		add_history(inpt);
		free(inpt);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	init_var(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	data->token = malloc(sizeof(t_token));
	data->cmd = malloc(sizeof(t_cmd));
	data->single_quote = false;
	data->double_quote = false;
}