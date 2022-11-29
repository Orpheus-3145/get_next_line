/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:19:27 by anonymous         #+#    #+#             */
/*   Updated: 2022/11/30 00:52:21 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_crs	*allocate_cursor(int fd)
{
	t_crs	*crs;

	crs = (t_crs *) malloc(sizeof(t_crs));
	if (! crs)
		return (NULL);
	crs->buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (! crs->buffer)
	{
		free(crs);
		crs = NULL;
		return (NULL);
	}
	crs->fd = fd;
	crs->pos = 0;
	crs->eof = 0;
	crs->reload = 1;
	return (crs);
}

int	has_n_line(t_crs *crs)
{
	while (crs->buffer[crs->pos] && crs->buffer[crs->pos] != '\n')
		(crs->pos)++;
	if (crs->buffer[crs->pos])
	{
		(crs->pos)++;
		return (1);
	}
	return (0);
}

char	*append_str(char *old, t_crs *crs, size_t start)
{
	size_t	len_old;
	size_t	len_right;
	char	*new_str;

	len_old = 0;
	if (old)
	{
		while (old[len_old])
			len_old++;
	}
	len_right = crs->pos - start;
	if (! len_right)
		return (NULL);
	new_str = (char *) malloc((len_old + len_right + 1) * sizeof(char));
	if (new_str)
	{
		new_str[len_old + len_right] = '\0';
		while (len_right--)
			new_str[len_old + len_right] = crs->buffer[start + len_right];
		while (len_old--)
			new_str[len_old] = old[len_old];
	}
	if (old)
		free(old);
	return (new_str);
}

int	fill_buffer(t_crs *crs)
{
	ssize_t	chars_read;

	if (crs->reload)
	{
		chars_read = read(crs->fd, crs->buffer, BUFFER_SIZE);
		if (chars_read == -1 || crs->eof)
			return (0);
		crs->eof = chars_read == 0;
		crs->reload = crs->eof;
		crs->buffer[chars_read] = '\0';
		crs->pos = 0;
	}
	return (1);
}

char	*read_line(t_crs *crs)
{
	size_t	start;
	char	*line;
	int		n_line;

	line = NULL;
	while (1)
	{
		if (! fill_buffer(crs))
		{
			if (line)
				free(line);
			return (NULL);
		}
		if (crs->eof)
			return (line);
		start = crs->pos;
		n_line = has_n_line(crs);
		line = append_str(line, crs, start);
		if (n_line)
			return (line);
		else
			crs->reload = 1;
	}
}
