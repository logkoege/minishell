#include "minishell.h"

char	*start_split(t_data *data, char *input)
{
	char	*str;

	str = delete_space(data, input);
	return (str);
}

char	*delete_space(t_data *data, char *input)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!str)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' && !data->double_quote)
			data->single_quote = !data->single_quote;
		else if (input[i] == '"' && !data->single_quote)
			data->double_quote = !data->double_quote;
		if (input[i] != ' ' || data->single_quote || data->double_quote || (j > 0 && str[j - 1] != ' '))
			str[j++] = input[i];
		i++;
	}
	if (j > 0 && str[j - 1] == ' ' && !data->single_quote && !data->double_quote)
		str[j - 1] = '\0';
	else
		str[j] = '\0';
	printf("str = %s\n", str);
	return (str);
}
