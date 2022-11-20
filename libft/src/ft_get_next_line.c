/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:10:14 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/23 23:09:59 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif
#define FREE -3

/*	Reads to the static char *remain until '\n' is found, or until
 *	EOF has been reached. If read() reaches EOF (returns nbyte < BUFF_SIZE)
 *	or attempts an invalid read() (returns -1) and remain doesn't
 *	end with '\n', get_line_len() returns 0.
 */
static long	get_line_len(char **remain, int fd)
{
	long	read_status;
	char	*read_buf;

	while (!(*remain) || !strlen_c(*remain, '\n'))
	{
		read_buf = malloc(BUFFER_SIZE + 1);
		read_status = read(fd, read_buf, BUFFER_SIZE);
		if (read_status <= 0)
		{
			free (read_buf);
			return (read_status);
		}
		read_buf[read_status] = 0;
		*remain = ft_strjoin_free(*remain, read_buf);
		free(read_buf);
	}
	return (strlen_c(*remain, '\n'));
}

/**
 * @brief	gnl() returns the next line from the file to which fd refers.
 * 			If fd is invalid, or of EOF has been reached, NULL will be returned
 * 			Each call to gnl() expects the user to free the returned string.		
 * 
 * @param fd : file descriptor 
 * @return char* : 	A malloced string including the '\n' if applicable.
 * 					NULL if fd == -1, or if EOF and remain is empty.
 */
char	*get_next_line(int fd)
{
	char		*current_line;
	long		line_len;
	static char	*remain = NULL;

	line_len = get_line_len(&remain, fd);
	if (line_len <= 0)
		line_len = strlen_c(remain, 0);
	if (!line_len)
	{
		free (remain);
		remain = (NULL);
		return (NULL);
	}
	current_line = malloc(line_len + 1);
	ft_strncpy(current_line, remain, line_len);
	if (!strlen_c(remain, '\n') || fd == FREE)
	{
		free (remain);
		remain = (NULL);
	}
	else
		ft_strncpy(remain, &remain[line_len], \
			strlen_c(remain, 0) - line_len + 1);
	return (current_line);
}
