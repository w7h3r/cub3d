/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keezgi <keezgi@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:33:25 by keezgi            #+#    #+#             */
/*   Updated: 2025/12/26 13:39:18 by keezgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

#include <stddef.h>

size_t  ft_strlen_gnl(char *str);
int		gnl_strchr(char *str, char a);
char	*gnl_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

#endif