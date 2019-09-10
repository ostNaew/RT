/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:58:04 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/17 16:17:00 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTERS_H
# define FILTERS_H

# define SIZE 6

# include "engine_render.h"

t_vector		negative_scale(t_vector *colors, size_t size);
t_vector		sepia_scale(t_vector *colors, size_t size);
t_vector		gray_scale(t_vector *colors, size_t size);
t_vector		blur(t_vector *colors, size_t size);
t_vector		median(t_vector *colors, size_t size);
t_vector		get_color_from_pixel(t_pixel pixel);

#endif
