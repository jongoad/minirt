/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:10:48 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/28 15:50:21 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_strjoin_free(char *s1, char const *s2);
size_t	strlen_c(char *s, char c);
char	*ft_strncpy(char *dest, char *src, size_t n);

#endif