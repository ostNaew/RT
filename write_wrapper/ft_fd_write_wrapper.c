/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_write_wrapper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:43:35 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:12:12 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write_wrapper.h"

static t_list *g_ww_fd_list;

static t_w_fd_wrapper	*get_current_by_fd(int fd)
{
	t_list			*tmp;
	t_w_fd_wrapper	*current;

	tmp = g_ww_fd_list;
	while (tmp)
		if (((t_w_fd_wrapper *)(tmp->content))->fd == fd)
			return ((t_w_fd_wrapper *)(tmp->content));
		else
			tmp = tmp->next;
	current = (t_w_fd_wrapper *)ft_memalloc(sizeof(t_w_fd_wrapper));
	current->fd = fd;
	tmp = (t_list *)ft_memalloc(sizeof(t_list));
	tmp->content = (void *)current;
	tmp->content_size = sizeof(t_w_fd_wrapper);
	ft_lstadd(&g_ww_fd_list, tmp);
	return (current);
}

static void				delete_fd(int fd)
{
	t_list *tmp;
	t_list *to_free;

	tmp = g_ww_fd_list;
	if (g_ww_fd_list && ((t_w_fd_wrapper *)(g_ww_fd_list->content))->fd == fd)
	{
		g_ww_fd_list = g_ww_fd_list->next;
		free(tmp->content);
		free(tmp);
	}
	else
		while (tmp && tmp->next)
			if (((t_w_fd_wrapper *)(tmp->next->content))->fd == fd)
			{
				to_free = tmp->next;
				tmp->next = tmp->next->next;
				free(to_free->content);
				free(to_free);
			}
			else
				tmp = tmp->next;
}

int						ft_fd_write_wrapper(int fd, const char *buf,
	size_t nbyte)
{
	t_w_fd_wrapper	*current;
	size_t			j;
	int				res;

	j = -1;
	res = (int)nbyte;
	if (WWRAPPER_BUF_SIZE > 0 && fd > -1 && (current = get_current_by_fd(fd)))
	{
		while (buf && ++j < nbyte)
		{
			if (current->i == WWRAPPER_BUF_SIZE && (current->i = 0) == 0)
				write(current->fd, current->buffer, WWRAPPER_BUF_SIZE);
			current->buffer[current->i++] = buf[j];
		}
		if (nbyte == 0)
		{
			write(current->fd, current->buffer, current->i);
			delete_fd(fd);
		}
	}
	else
		return (write(fd, buf, nbyte));
	return (res);
}
