#include "minishell.h"

int main(void)
{
	char *input = "bonjour je m'appelle logkoege";
	char *ssr;
	int i;
	int j;
	t_data *data;

	ssr = malloc(sizeof(char) * (ft_strlen(input) + 1));
	while (input[i])
	{
		
		lstadd_back(data, lstnew(tokenizer(data, ssr), ssr));
	}
}