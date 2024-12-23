/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:36:33 by ldei-sva          #+#    #+#             */
/*   Updated: 2024/12/22 21:58:18 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		is_there_newline(char *stack);
char	*ft_strjoin(char	*stack, char	*fileread);
int		ft_strlen(char *str);

#endif
