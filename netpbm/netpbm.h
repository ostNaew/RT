/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   netpbm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:32:07 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/21 15:13:32 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETPBM_H
# define NETPBM_H
# define FILE_ERROR -1
# define INVALID_FORMAT -2

# include <stdlib.h>

typedef struct	s_netpbm_image
{
	int		*image_data;
	size_t	width;
	size_t	height;
}				t_netpbm_image;

t_netpbm_image	read_image(const char *file, int *status);

#endif
