/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:23:02 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/28 17:37:39 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*list_free(t_list *list)
{
	t_list *buf;

	while (list && (buf = list))
	{
		list = list->next;
		ft_memdel(&buf->content);
		ft_memdel((void **)&buf);
	}
	return (NULL);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *list;
	t_list *tmp;

	new = NULL;
	if (lst && f)
	{
		tmp = f(lst);
		lst = lst->next;
		list = malloc(sizeof(t_list));
		ft_memcpy(list, tmp, sizeof(t_list));
		new = list;
		while (lst && new)
		{
			if (!(tmp = f(lst)))
				return ((t_list *)list_free(new));
			list->next = malloc(sizeof(t_list));
			ft_memcpy(list->next, tmp, sizeof(t_list));
			lst = lst->next;
			list = list->next;
		}
	}
	return (new);
}
