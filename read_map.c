/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:14:13 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:42:45 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write_wrapper.h"
#include <fcntl.h>

char	*read_map(char *filename)
{
	t_wwrapper	wrap;
	char		buf[128];
	char		*res;
	int			fd;
	int			rd;

	res = NULL;
	wrap.type = 2;
	wrap.content.str_ptr = &res;
	wrap.size = 0;
	wrap.bytes_written = 0;
	if ((fd = open(filename, O_RDONLY)) > 0)
		while ((rd = read(fd, buf, 128)) > 0)
			ft_write_wrapper(&wrap, buf, (size_t)rd);
	ft_write_wrapper(&wrap, buf, 0);
	close(fd);
	return (res);
}
