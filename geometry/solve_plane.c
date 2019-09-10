/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:05:09 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:22 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

double		plane_solve_x(t_plane_equation plane, double y, double z)
{
	return (-(plane.b * y + plane.c * z + plane.d) / plane.a);
}

double		plane_solve_y(t_plane_equation plane, double x, double z)
{
	return (-(plane.a * x + plane.c * z + plane.d) / plane.b);
}

double		plane_solve_z(t_plane_equation plane, double x, double y)
{
	return (-(plane.a * x + plane.b * y + plane.d) / plane.c);
}
