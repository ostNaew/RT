/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_wrapper.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:46:46 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:13:18 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WRITE_WRAPPER_H
# define FT_WRITE_WRAPPER_H

# include "libft.h"

# define WWRAPPER_BUF_SIZE 36

typedef struct	s_w_fd_wrapper
{
	char	buffer[WWRAPPER_BUF_SIZE];
	int		fd;
	size_t	i;
}				t_w_fd_wrapper;

typedef struct	s_wwrapper
{
	unsigned char	type;
	union		u_content
	{
		int		fd;
		char	*str;
		char	**str_ptr;
	}				content;
	long			bytes_written;
	size_t			size;
}				t_wwrapper;

int				ft_fd_write_wrapper(int fd, const char *buf, size_t nbyte);
int				ft_write_wrapper(t_wwrapper *wrap, const char *buf,
					size_t nbyte);

#endif
