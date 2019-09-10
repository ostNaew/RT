/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:19:52 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/16 17:03:34 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnlfd	*find_file(int fd, t_list **fd_list)
{
	t_list	*current;
	t_gnlfd	*file;

	if (*fd_list)
	{
		current = *fd_list;
		while (current)
			if (((t_gnlfd *)(current->content))->fd == fd)
				return ((t_gnlfd *)current->content);
			else
				current = current->next;
	}
	if ((file = (t_gnlfd *)ft_memalloc(sizeof(t_gnlfd))))
	{
		file->fd = fd;
		file->buf = ft_strnew(0);
		current = ft_lstnew(file, sizeof(t_gnlfd));
		ft_memdel((void **)&file);
	}
	if (current)
	{
		ft_lstadd(fd_list, current);
		return ((t_gnlfd *)current->content);
	}
	return (NULL);
}

static int		read_line(t_gnlfd *file, char **line)
{
	int		rd;
	char	buf[BUFF_SIZE + 1];
	char	*s;
	char	*end;

	rd = 1;
	ft_memset(buf, 0, BUFF_SIZE + 1);
	s = NULL;
	end = ft_strchr(file->buf, '\n');
	while (!end && (rd = read(file->fd, buf, BUFF_SIZE)))
	{
		s = file->buf;
		file->buf = ft_strjoin(s, buf);
		ft_strdel(&s);
		end = ft_strchr(file->buf, '\n');
		ft_memset(buf, 0, BUFF_SIZE);
	}
	rd = !(rd == 0 && ft_strcmp(file->buf, "\0") == 0);
	*line = end ? ft_strsub(file->buf, 0, end - file->buf) : file->buf;
	s = end ? file->buf : NULL;
	file->buf = end ? ft_strdup(end + 1) : ft_strdup("\0");
	ft_strdel(&s);
	return (rd);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*fd_list;
	t_gnlfd			*file;
	char			c;

	if (fd < 0)
		return (-1);
	file = find_file(fd, &fd_list);
	if (!line || read(fd, &c, 0) < 0 || !file)
		return (-1);
	return (read_line(file, line));
}
