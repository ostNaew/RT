/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:50:36 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/17 18:48:50 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_TRACING_H
# define PATH_TRACING_H

# include "engine_render.h"

typedef enum	e_probability_type
{
	ALBEDO,
	SPECULAR,
	REFRACTION,
}				t_probability_type;

int				fits_probability(double probability, t_material *material,
					t_probability_type type);
void			albedo_ray(t_ray *ray, t_intersection intersection,
					t_vector *signal);
void			specular_ray(t_ray *ray, t_intersection intersection,
					t_vector *signal);
void			refraction_ray(t_ray *ray, t_intersection intersection,
					t_vector *signal);

#endif
