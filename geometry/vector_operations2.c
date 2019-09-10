/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 22:00:36 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:36 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
	return (v1);
}

double		vectors_angle(t_vector v1, t_vector v2)
{
	v1 = normalize(v1);
	v2 = normalize(v2);
	return (acos(dot(v1, v2)));
}
