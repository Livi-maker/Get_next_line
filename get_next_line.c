/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:32:34 by ldei-sva          #+#    #+#             */
/*   Updated: 2024/12/22 21:36:16 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*uploadstack(char *stack)
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

char	*setmemory(char *stack, char *fileread, int len, int byte_read)
{
	int		i;
	char	*temp;

	if (stack && len == ft_strlen(stack) && byte_read < BUFFER_SIZE)
	{
		free (stack);
		stack = NULL;
	}
	else if (stack)
	{
		temp = stack;
		stack = uploadstack(stack + len);
		free (temp);
	}
	if (!stack && len < ft_strlen(fileread))
	{
		i = 0;
		fileread += len;
		stack = malloc ((ft_strlen(fileread) + 1) * (sizeof(char)));
		while (*fileread)
		{
			stack[i] = *fileread;
			fileread++;
			i++;
		}
		stack[i] = '\0';
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
	line[i] = '\0';
	return (line);
}

char	*search_for_newline(char *stack, char *fileread, char *line)
{
	int		index;

	index = 0;
	if (stack != NULL)
	{
		while (stack[index] != '\n')
			index++;
		line = createstr(index + 1, stack, line);
		return (line);
	}
	while (fileread[index] != '\n' && fileread[index] != '\0')
		index++;
	line = createstr(index + 1, fileread, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*stack = NULL;
	char			*fileread;
	int				byte_read;
	char			*line = NULL;
	char			*temp;

	fileread = malloc (BUFFER_SIZE + 1);
	if (fileread == NULL)
		return (NULL);
	if (stack == NULL || (stack && is_there_newline(stack) == 0))
	{
		byte_read = read(fd, fileread, BUFFER_SIZE);
		if (byte_read == -1 || (stack == NULL && byte_read == 0))
		{
			free (fileread);
			return (NULL);
		}
		fileread[byte_read] = '\0';
		if (stack)
		{
			temp = stack;
			stack = ft_strjoin(stack, fileread);
			free (temp);
		}
	}
	line = search_for_newline(stack, fileread, line);
	stack = setmemory(stack, fileread, ft_strlen(line), byte_read);
	free (fileread);
	return (line);
}

/*int	main()
{
	int	fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0)
		return (1);
	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
}*/
