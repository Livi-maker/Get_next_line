/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:32:34 by ldei-sva          #+#    #+#             */
/*   Updated: 2024/12/23 12:02:07 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*updatestack(char *stack)
{
	char	*temp;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(stack);
	temp = malloc ((size + 1) * (sizeof(char)));
	while (*stack)
	{
		temp[i] = *stack;
		i++;
		stack++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*setmemory(char *stack, int len, int byte_read)
{
	int		i;
	char	*temp;

	if (stack && len == ft_strlen(stack))
	{
		free (stack);
		stack = NULL;
	}
	else if (stack)
	{
		temp = stack;
		stack = updatestack(stack + len);
		free (temp);
	}
	return (stack);
}

char	*createstr(int index, char *fileread, char *line)
{
	int		i;

	line = malloc((index + 1) * (sizeof(char)));
	i = 0;
	while (i < index)
	{
		line[i] = fileread[i];
		i++;
	}
	line[i] = fileread[i];
	return (line);
}

char	*search_for_newline(char *stack, char *fileread, char *line)
{
	int		index;

	index = 0;
	while (stack[index] != '\n' && stack[index] != '\0')
		index++;
	line = createstr(index + 1, stack, line);
	return (line);
}

int	readfile(int fd, char *fileread)
{
	int	byte_read;

	byte_read = read(fd, fileread, BUFFER_SIZE);
	if (byte_read < 0)
		return (-1);
	fileread[byte_read] = '\0';
	return (byte_read);
}

char	*get_next_line(int fd)
{
	static char		*stack = NULL;
	char			*fileread = NULL;
	int				byte_read;
	char			*line = NULL;
	char			*temp;

	fileread = malloc (BUFFER_SIZE + 1);
	byte_read = 1;
	if (fileread == NULL)
		return (NULL);
	while (is_there_newline(stack) == 0 || byte_read == 0)
	{
		byte_read = readfile(fd, fileread);
		if (byte_read == -1 || (!stack && byte_read == 0))
		{
			free (fileread);
			return (NULL);
		}
		temp = stack;
		stack = ft_strjoin(stack, fileread);
		if (temp)
			free (temp);
	}
	line = search_for_newline(stack, fileread, line);
	stack = setmemory(stack, ft_strlen(line), byte_read);
	free (fileread);
	return (line);
}

int	main()
{
	int	fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0)
		return (1);
	while (line != NULL)
	{
		printf("%slinea\n", line);
		line = get_next_line(fd);
	}
}
