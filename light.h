/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:47:41 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/16 15:14:56 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "engine_render.h"
# include "worthless_geometry.h"

typedef struct	s_lighting
{
	t_scene			*scene;
	t_intersection	intersection;
	t_vector		view_direction;
	t_vector		normal;
	t_vector		point;
	double			specular_exponent;
	double			light_distance;
}				t_lighting;

void			process_point_light(t_lighting lighting, t_lightsource light,
					double *diffuse, double *specular);
void			process_parallel_light(t_lighting lighting,
					t_lightsource light, double *diffuse, double *specular);
void			process_directional_light(t_lighting lighting,
					t_lightsource light, double *diffuse, double *specular);

#endif
