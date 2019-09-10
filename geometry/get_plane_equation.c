/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane_equation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:39:02 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:01 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_plane_equation	get_plane_equation(t_vector normal, t_vector point)
{
	t_plane_equation res;

	res.a = normal.x;
	res.b = normal.y;
	res.c = normal.z;
	res.d = -(normal.x * point.x + normal.y * point.y + normal.z * point.z);
	return (res);
}
