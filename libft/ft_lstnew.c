/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:01:02 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/27 16:20:23 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;
	void	*cont;

	res = (t_list *)ft_memalloc(sizeof(t_list));
	if (res && content && content_size)
	{
		if ((cont = ft_memalloc(content_size)))
		{
			ft_memcpy(cont, content, content_size);
			res->content = cont;
			res->content_size = content_size;
		}
		else
			ft_memdel((void **)&res);
	}
	return (res);
}
