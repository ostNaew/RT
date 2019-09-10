/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:54:13 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:10 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

double	norm(t_vector v)
{
	return (sqrt(norm2(v)));
}

double	norm2(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
