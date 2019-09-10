/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:10:22 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/02 15:39:39 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

# include <stdlib.h>

typedef enum	e_json_value_type
{
	JSON_OBJECT,
	JSON_ARRAY,
	JSON_STRING,
	JSON_NUMBER,
	JSON_BOOL,
	JSON_NULL
}				t_json_value_type;

typedef struct	s_json
{
	union		u_json_value
	{
		struct s_json	*object;
		struct s_json	*array;
		char			*string;
		long double		number;
		int				boolean;
	}					value;
	char				*key;
	size_t				size;
	t_json_value_type	type;
}				t_json;

t_json			new_json(void);
t_json			json_parse(char *json_string);
void			json_destroy(t_json *json);
t_json			json_value_by_index(t_json json, size_t index);
t_json			json_value_by_key(t_json json, char *key);

#endif
