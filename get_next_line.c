/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:16:56 by anonymous         #+#    #+#             */
/*   Updated: 2022/11/29 23:34:25 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line;
	static t_crs	*crs;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (! crs)
	{
		crs = allocate_cursor(fd);
		if (! crs)
			return (NULL);
	}
	line = read_line(crs);
	if (! line)
	{
		free(crs->buffer);
		free(crs);
		crs = NULL;
	}
	return (line);
}
