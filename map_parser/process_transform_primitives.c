/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_transform_primitives.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:19:39 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/24 17:24:29 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

static void	move_primitive(t_primitive *primitive, t_vector position)
{
	if (primitive->type == PLANE)
		*((t_triangle*)primitive->primitive) = move_triangle(
				*((t_triangle*)primitive->primitive), position);
	if (primitive->type == TRIANGLE)
		*((t_triangle*)primitive->primitive) = move_triangle(
				*((t_triangle*)primitive->primitive), position);
	if (primitive->type == CIRCLE)
		((t_circle*)primitive->primitive)->plane = move_triangle(
				((t_circle*)primitive->primitive)->plane, position);
	if (primitive->type == SPHERE)
		*((t_sphere*)primitive->primitive) = move_sphere(
				*((t_sphere*)primitive->primitive), position);
	if (primitive->type == CONE)
		*((t_cone*)primitive->primitive) = move_cone(
				*((t_cone*)primitive->primitive), position);
	if (primitive->type == CYLINDER)
		*((t_cylinder*)primitive->primitive) = move_cylinder(
				*((t_cylinder*)primitive->primitive), position);
	if (primitive->type == PARABOLOID)
		*((t_paraboloid*)primitive->primitive) = move_paraboloid(
				*((t_paraboloid*)primitive->primitive), position);
	if (primitive->type == TORUS)
		*((t_torus*)primitive->primitive) = move_torus(
				*((t_torus*)primitive->primitive), position);
}

void		process_translation_primitives(t_render *render, size_t index,
				t_vector position)
{
	size_t	i;

	i = -1;
	while (++i < render->scene.objects[index].n_primitives)
		move_primitive(&render->scene.objects[index].primitives[i], position);
}

static void	rotation_primitive(t_primitive *primitive, t_4x4matrix rotation)
{
	if (primitive->type == PLANE)
		*((t_triangle*)primitive->primitive) = transform_triangle_ws(
				*((t_triangle*)primitive->primitive), rotation);
	if (primitive->type == TRIANGLE)
		*((t_triangle*)primitive->primitive) = transform_triangle_ws(
				*((t_triangle*)primitive->primitive), rotation);
	if (primitive->type == CIRCLE)
		((t_circle*)primitive->primitive)->plane = transform_triangle_ws(
				((t_circle*)primitive->primitive)->plane, rotation);
	if (primitive->type == SPHERE)
		*((t_sphere*)primitive->primitive) = transform_sphere_ws(
				*((t_sphere*)primitive->primitive), rotation);
	if (primitive->type == CONE)
		*((t_cone*)primitive->primitive) = transform_cone_ws(
				*((t_cone*)primitive->primitive), rotation);
	if (primitive->type == CYLINDER)
		*((t_cylinder*)primitive->primitive) = transform_cylinder_ws(
				*((t_cylinder*)primitive->primitive), rotation);
	if (primitive->type == TORUS)
		*((t_torus*)primitive->primitive) = transform_torus_ws(
				*((t_torus*)primitive->primitive), rotation);
}

void		process_rotation_primitives(t_render *render, size_t index,
				t_4x4matrix rotation)
{
	size_t	i;

	i = -1;
	while (++i < render->scene.objects[index].n_primitives)
		rotation_primitive(&render->scene.objects[index].primitives[i],
				rotation);
}
