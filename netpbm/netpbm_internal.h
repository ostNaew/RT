/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   netpbm_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:35:46 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/13 15:55:54 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETPBM_INTERNAL_H
# define NETPBM_INTERNAL_H

# include "netpbm.h"
# include "fcntl.h"
# include "libft.h"

t_netpbm_image	new_image(void);
t_netpbm_image	form_image(size_t width, size_t height);
int				read_number(int fd, size_t *num);
int				read_meta(int fd, size_t *width, size_t *height,
					size_t *maxval);
t_netpbm_image	read_pbm_ascii(int fd, int *status);
t_netpbm_image	read_pbm_binary(int fd, int *status);
t_netpbm_image	read_pgm_ascii(int fd, int *status);
t_netpbm_image	read_pgm_binary(int fd, int *status);
t_netpbm_image	read_ppm_ascii(int fd, int *status);
t_netpbm_image	read_ppm_binary(int fd, int *status);

#endif
