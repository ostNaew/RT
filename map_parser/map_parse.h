/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 21:21:53 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/24 17:25:28 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSE_H
# define MAP_PARSE_H

# include "json.h"
# include "engine_render.h"
# include "worthless_geometry.h"

t_vector	json2vec(t_json json, int w);
int			process_camera(t_render *render, t_json json);
int			process_materials(t_render *render, t_json json);
int			process_lights(t_render *render, t_json json);
int			process_objects(t_render *render, t_json json_obj);
int			process_transformations(t_render *render, t_json json);

/*
**primitive's property
*/

int			add_toruss_values(void **primitive, t_json json);
int			add_paraboloids_values(void **primitive, t_json json);
int			add_cones_values(void **primitive, t_json json);
int			add_cylinders_values(void **primitive, t_json json);
int			add_spheres_values(void **primitive, t_json json);
int			add_planes_values(void **primitive,
				t_primitive_type type, t_json json);
int			add_type(t_primitive_type *type, char *str);
int			add_material(t_render *render, t_material **material,
				t_json json);
int			add_texture(t_render *render, t_texture *texture, t_json json);
int			add_color(int *color, t_json json);
int			get_rotation_matrix(t_json json, t_4x4matrix *rotation);
int			add_boundary(t_object *object, t_json json);
void		process_rotation_primitives(t_render *render, size_t index,
				t_4x4matrix rotation);
void		process_translation_primitives(t_render *render, size_t index,
				t_vector position);
int			process_images(t_render *render, t_json json, int load_images);
int			atoi_hex(char *str);

#endif
