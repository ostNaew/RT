/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:08:43 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/14 17:12:14 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct	s_init_data
{
	char	*host;
	char	*map;
	int		port;
	char	master;
}				t_init_data;

#endif
