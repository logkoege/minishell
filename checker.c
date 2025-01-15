#include "minishell.h"

int	is_ws(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int	check_pipe(char *input)
{
    int	i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '|')
        {
            i++;
            while (input[i] && is_ws(input[i]))
                i++;
            if (input[i] == '|' || input[i] == '\0')
            {
                printf("syntax error near unexpected token '|'\n");
                return (0);
            }
        }
        else
            i++;
    }
    return (1);
}

int	check_double_redirect(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<'))
        {
            i += 2;
            while (input[i] && is_ws(input[i]))
                i++;
            if (input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '\0')
            {
                printf("syntax error near unexpected token '%c%c'\n", input[i - 2], input[i - 1]);
                return (0);
            }
        }
        else
            i++;
    }
    return (1);
}

int	check_other(char *input)
{
    int	i;

    i = 0;
    while (input[i])
    {
        if ((input[i] == '>' || input[i] == '<') && (input[i + 1] != '>' && input[i + 1] != '<'))
        {
            i++;
            while (input[i] && is_ws(input[i]))
                i++;
            if (input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '\0')
            {
                printf("syntax error near unexpected token '%c'\n", input[i - 1]);
                return (0);
            }
        }
        else if (check_double_redirect(&input[i]) == 0)
            return (0);
        else
            i++;
    }
    return (1);
}

int	check_invalid_combinations(char *input)
{
    int	i;

    i = 0;
    while (input[i])
    {
        if ((input[i] == '>' || input[i] == '<') && (input[i + 1] == '>' || input[i + 1] == '<'))
        {
            printf("syntax error near unexpected token '%c%c'\n", input[i], input[i + 1]);
            return (0);
        }
        i++;
    }
    return (1);
}

void	track(int *i, int *j, char *input, char n)
{
	if (input[*i] == n)
	{
		if (*i != 0 && input[*i - 1] != ' ')
			(*j)++;
		if (input[*i + 1] == n)
		{
			(*i)++;
			if (input[*i + 1] != ' ' && input[*i])
			{
				(*j)++;
			}
		}
		else if (input[*i + 1] != ' ' && input[*i + 1] != '\0')
			(*j)++;
	}
}

int	token_is_valid(char *input)
{
    int	i;

    i = 0;
    while (input[i])
    {
        if (check_pipe(&input[i]) == 0)
            return (0);
        if (check_other(&input[i]) == 0)
            return (0);
        if (check_invalid_combinations(&input[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}
