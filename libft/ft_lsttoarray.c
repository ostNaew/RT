/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:00:14 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/01 20:51:09 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lsttoarray(t_list *list)
{
	void	*res;
	size_t	size;
	t_list	*lst;

	res = NULL;
	size = 1;
	lst = list;
	while (lst && (size += lst->content_size))
		lst = lst->next;
	lst = list;
	if (--size)
	{
		res = ft_memalloc(size);
		size = 0;
		while (lst)
		{
			ft_memcpy(res + size, lst->content, lst->content_size);
			size += lst->content_size;
			lst = lst->next;
		}
	}
	return (res);
}
