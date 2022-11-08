/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 01:16:32 by anonymous     #+#    #+#                 */
/*   Updated: 2022/11/04 17:58:23 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE 2147483648
#  define BUFFER_SIZE 2147483647
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_crs
{
	char			*buffer;
	size_t			pos;
	int				fd;
	int				eof;
	int				reload;
}	t_crs;

char	*get_next_line(int fd);

t_crs	*allocate_cursor(int fd);

int		has_n_line(t_crs *crs);

char	*append_str(char *left, t_crs *crs, size_t start);

int		fill_buffer(t_crs *crs);

char	*read_line(t_crs *crs);

#endif