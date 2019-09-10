/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_brightness.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:33:32 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/17 15:13:31 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filters.h"

double	get_index_brightness(double scale)
{
	static double	brightness = 1.;

	brightness *= scale;
	return (brightness);
}
