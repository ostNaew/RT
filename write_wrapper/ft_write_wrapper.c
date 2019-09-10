/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:44:15 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/14 17:56:09 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write_wrapper.h"

static int	ft_write_to_string(t_wwrapper *wrap, const char *buf,
	size_t nbyte)
{
	if (wrap && buf && nbyte)
	{
		if (wrap->size == 0 ||
			((size_t)wrap->bytes_written + nbyte + 1) < wrap->size)
		{
			ft_strncat(wrap->content.str, buf, nbyte);
			return ((int)nbyte);
		}
		if ((size_t)wrap->bytes_written + 1 < wrap->size)
		{
			ft_strncat(wrap->content.str, buf,
				(size_t)wrap->bytes_written - wrap->size - 1);
			return ((int)(wrap->size - (size_t)wrap->bytes_written - 1));
		}
	}
	return (nbyte == 0 ? 0 : -1);
}

static int	ft_write_and_realloc(t_wwrapper *wrap, const char *buf,
	size_t nbyte)
{
	char *tmp;

	if (wrap && buf && nbyte)
	{
		if (((size_t)wrap->bytes_written + nbyte) >= wrap->size)
		{
			tmp = *(wrap->content.str_ptr);
			*(wrap->content.str_ptr) =
				(char*)ft_strnew((size_t)wrap->bytes_written + nbyte);
			if (tmp)
				ft_strcpy(*(wrap->content.str_ptr), tmp);
			free(tmp);
		}
		if (*(wrap->content.str_ptr))
		{
			ft_strncat(*(wrap->content.str_ptr), buf, nbyte);
			return ((int)nbyte);
		}
	}
	return (-1);
}

int			ft_write_wrapper(t_wwrapper *wrap, const char *buf,
	size_t nbyte)
{
	int res;

	res = 0;
	if (wrap && buf)
	{
		if (wrap->type == 0)
			res = ft_fd_write_wrapper(wrap->content.fd, buf, nbyte);
		else if (wrap->type == 1)
			res = ft_write_to_string(wrap, buf, nbyte);
		else if (wrap->type == 2)
			res = ft_write_and_realloc(wrap, buf, nbyte);
		if (res > 0)
			wrap->bytes_written += res;
		return (res);
	}
	return (-1);
}
