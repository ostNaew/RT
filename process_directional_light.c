/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_directional_light.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:11:35 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:48:32 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

void	process_directional_light(t_lighting lighting, t_lightsource light,
	double *diffuse, double *specular)
{
	t_vector	direction;

	direction = normalize(vector_sub(lighting.point, light.position));
	if (acos(dot(direction, light.direction)) > light.angle)
		return ;
	process_point_light(lighting, light, diffuse, specular);
}
