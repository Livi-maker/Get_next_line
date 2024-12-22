#include "get_next_line.h"

int	is_there_newline(char *stack)
{
	int	i;

	i = 0;
	while (stack[i])
	{
		if (stack[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *stack, char *fileread)
{
	char	*temp;
	int		size;
	int		i;
	int		i2;

	size = ft_strlen(stack) + ft_strlen(fileread);;
	i = 0;
	i2 = 0;
	temp = malloc ((size + 1) * (sizeof(char)));
	while (stack[i])
	{
		temp[i] = stack[i];
		i++;
	}
	while (fileread[i2])
	{
		temp[i] = fileread[i2];
		i2++;
		i++;
	}
	temp[i] = '\0';
	return(temp);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}
