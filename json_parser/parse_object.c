/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:38:52 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/13 14:28:08 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

static void		finalize_object(t_json *json, t_list **list, int *status)
{
	if (*status == 0)
	{
		json->type = JSON_OBJECT;
		json->size = ft_lstsize(*list);
		json->value.array = (t_json*)ft_lsttoarray(*list);
		ft_lstdestroy(list);
	}
	else
		ft_lstdel(list, json_del);
}

static t_json	get_property(char **json_string, int *status)
{
	t_json	res;
	char	*key;

	res = new_json();
	if (!(key = get_string(json_string)))
	{
		*status = -1;
		return (res);
	}
	skip_spaces(json_string);
	if (**json_string != ':')
	{
		*status = -1;
		free(key);
		return (res);
	}
	*json_string += 1;
	skip_spaces(json_string);
	res = parse_element(json_string, status);
	res.key = key;
	skip_spaces(json_string);
	if (**json_string != ',' && **json_string != '}')
		*status = -1;
	return (res);
}

int				add_property_to_list(t_list **list, t_list *property)
{
	t_list	*lst;

	lst = *list;
	while (lst)
	{
		if (ft_strequ(((t_json*)lst->content)->key,
				((t_json*)property->content)->key))
		{
			ft_lstadd(list, property);
			return (-1);
		}
		lst = lst->next;
	}
	ft_lstaddtail(list, property);
	return (0);
}

t_json			parse_object(char **json_string, int *status)
{
	t_list	*list;
	t_json	elem;
	t_json	res;

	res = new_json();
	*json_string += 1;
	*status = 0;
	list = NULL;
	skip_spaces(json_string);
	while (**json_string && **json_string != '}' && *status == 0)
	{
		skip_spaces(json_string);
		if (element_lack(json_string, status, '}'))
			break ;
		elem = get_property(json_string, status);
		if (add_property_to_list(&list, ft_lstnew(&elem, sizeof(t_json))))
		{
			*status = -1;
			break ;
		}
	}
	finalize_object(&res, &list, status);
	*json_string += 1;
	return (res);
}
