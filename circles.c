/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:51:27 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/10 17:17:18 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_circle	new_circle(double radius)
{
	return ((t_circle){
			.plane = new_triangle(100., 100.),
			.radius = radius
			});
}

t_circle	move_circle(t_circle circle, t_vector vector)
{
	circle.plane = move_triangle(circle.plane, vector);
	return (circle);
}

t_circle	rotate_circle_os(t_circle circle, double x_angle, double y_angle,
	double z_angle)
{
	circle.plane = rotate_triangle_os(circle.plane, x_angle, y_angle, z_angle);
	return (circle);
}

t_circle	transform_circle_ws(t_circle circle, t_4x4matrix matrix)
{
	circle.plane = transform_triangle_ws(circle.plane, matrix);
	return (circle);
}
