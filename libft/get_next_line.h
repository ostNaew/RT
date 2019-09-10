/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:52:27 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/12/04 20:57:03 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 48
# include "libft.h"

typedef struct	s_gnlfd
{
	int		fd;
	char	*buf;
}				t_gnlfd;

int				get_next_line(const int fd, char **line);

#endif
