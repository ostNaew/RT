/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_meta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 17:34:48 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/13 16:01:39 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "netpbm_internal.h"

static char	skip_spaces(int fd)
{
	char	buf;

	while (read(fd, &buf, 1) == 1)
		if (!ft_isspace(buf))
			return (buf);
	return ('\0');
}

int			read_number(int fd, size_t *num)
{
	char	buf;

	if (read(fd, &buf, 1) <= 0)
		return (FILE_ERROR);
	while (1)
		if (buf == '#')
			while (read(fd, &buf, 1) > 0 && buf != '\n')
				;
		else if (ft_isspace(buf))
			buf = skip_spaces(fd);
		else if (ft_isdigit(buf))
		{
			*num = buf - '0';
			while (read(fd, &buf, 1) > 0)
				if (ft_isdigit(buf))
					*num = *num * 10 + (buf - '0');
				else
					return (0);
		}
		else
			break ;
	return (FILE_ERROR);
}

int			read_meta(int fd, size_t *width, size_t *height, size_t *maxval)
{
	*width = 0;
	*height = 0;
	*maxval = 0;
	if (read_number(fd, width))
		return (FILE_ERROR);
	if (read_number(fd, height))
		return (FILE_ERROR);
	if (read_number(fd, maxval))
		return (FILE_ERROR);
	return (0);
}
