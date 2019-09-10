/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:22:10 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/01 19:39:50 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

static void	finalize_array(t_json *json, t_list **list, int *status)
{
	if (*status == 0)
	{
		json->type = JSON_ARRAY;
		json->size = ft_lstsize(*list);
		json->value.array = (t_json*)ft_lsttoarray(*list);
		ft_lstdestroy(list);
	}
	else
		ft_lstdel(list, json_del);
}

t_json		parse_array(char **json_string, int *status)
{
	t_list	*list;
	t_json	elem;
	t_json	res;

	res = new_json();
	*json_string += 1;
	*status = 0;
	list = NULL;
	skip_spaces(json_string);
	while (**json_string && **json_string != ']' && *status == 0)
	{
		skip_spaces(json_string);
		if (element_lack(json_string, status, ']'))
			break ;
		elem = parse_element(json_string, status);
		skip_spaces(json_string);
		if (**json_string != ',' && **json_string != ']')
			*status = -1;
		ft_lstaddtail(&list, ft_lstnew(&elem, sizeof(t_json)));
	}
	finalize_array(&res, &list, status);
	*json_string += 1;
	return (res);
}
