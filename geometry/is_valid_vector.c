/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 20:08:49 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/20 16:20:20 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

int	is_valid_vector(t_vector vector)
{
	return (!isnan(vector.x) && !isnan(vector.y) &&
			!isnan(vector.z) && !isnan(vector.w));
}
