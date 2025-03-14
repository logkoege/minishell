
#include "../includes/minishell.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static int	ft_nbrlen(int n)
{
	int	len;

	len = 1;
	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int exit_code)
{
	static int		len;
	int		is_negative;
	char	*result;

	len = ft_nbrlen(exit_code);
	is_negative = (exit_code < 0);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = ft_abs(exit_code % 10) + '0';
		exit_code /= 10;
	}
	if (is_negative)
		result[0] = '-';
	return (result);
}

void	remove_dollar(t_first *tmp2, char *str, int i, bool quote, t_data *data)
{
	int		c;
	int		j;
	char	*str2;

	j = 0;
	c = 0;
	str2 = malloc(sizeof(char) * 6);
	while (j < i - 1)
	{
		str[j] = tmp2->str[j];
		j++;
	}
	if (tmp2->str[i] == '?')
	{
		str2 = ft_itoa(data->exit_code);
		while(str2[c])
			str[j++] = str2[c++];
		i++;
		while (tmp2->str[i])
			str[j++] = tmp2->str[i++];
		str[j] = '\0';
		free(tmp2->str);
		tmp2->str = str;
		free(str2);
		return ;
	}
	else if (tmp2->str[i] == '$')
	{
		str2 = ft_itoa(getpid());
		while(str2[c])
			str[j++] = str2[c++];
		i++;
		while (tmp2->str[i])
			str[j++] = tmp2->str[i++];
		str[j] = '\0';
		free(tmp2->str);
		tmp2->str = str;
		free(str2);
		return ;
	}
	else if (is_digit(tmp2->str[i]))
	{
		tmp2->str = ft_dup_digit(tmp2->str, i - 1);
		free(str);
		return ;
	}
	else if (quote == true && tmp2->str[i] == '\"')
	{
		tmp2->str = ft_dup(tmp2->str);
		free(str);
		return ;
	}
	else if ((quote == false) && (tmp2->str[i] == '\"' || tmp2->str[i] == '\''))
	{
		tmp2->str = ft_dup_digit(tmp2->str, i - 1);
		free(str);
		return ;
	}
	else if ((tmp2->str[i] == ' ' || tmp2->str[i] == '\0' || tmp2->str[i] == '\"'))
	{
		tmp2->str = ft_dup(tmp2->str);
		free(str);
		return ;
	}
	i++;
	while (tmp2->str[i] != '$' && tmp2->str[i] != ' ' && tmp2->str[i] != '\0'
		&& tmp2->str[i] != '\"')
	{
		i++;
	}
	while (tmp2->str[i])
	{
		str[j] = tmp2->str[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(tmp2->str);
	tmp2->str = str;
}
