/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:59:00 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/02 15:39:48 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_INTERNAL_H
# define JSON_INTERNAL_H

# include "json.h"
# include "libft.h"
# include <math.h>

void	json_del(void *content, size_t size);
int		element_lack(char **json_string, int *status, char end);
void	skip_spaces(char **json_string);
char	*get_string(char **json_string);

t_json	parse_string(char **json_string, int *status);
t_json	parse_number(char **json_string, int *status);
t_json	parse_bool(char **json_string, int *status);
t_json	parse_null(char **json_string, int *status);

t_json	parse_element(char **json_string, int *status);
t_json	parse_array(char **json_string, int *status);
t_json	parse_object(char **json_string, int *status);

#endif
