/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_in_triangle_2d.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:06:32 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:13 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

int	point_in_triangle_2d(t_triangle triangle, t_vector point)
{
	double	b1;
	double	b2;
	double	b3;

	b1 = (triangle.a.x - point.x) * (triangle.b.y - triangle.a.y) -
		(triangle.b.x - triangle.a.x) * (triangle.a.y - point.y);
	b2 = (triangle.b.x - point.x) * (triangle.c.y - triangle.b.y) -
		(triangle.c.x - triangle.b.x) * (triangle.b.y - point.y);
	b3 = (triangle.c.x - point.x) * (triangle.a.y - triangle.c.y) -
		(triangle.a.x - triangle.c.x) * (triangle.c.y - point.y);
	if ((b1 <= 0. && b2 <= 0. && b3 <= 0.) ||
		(b1 >= 0. && b2 >= 0. && b3 >= 0.))
		return (1);
	return (0);
}
