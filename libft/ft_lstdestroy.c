/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdestroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:04:05 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/20 16:32:26 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del(void *content, size_t size)
{
	(void)size;
	free(content);
}

void		ft_lstdestroy(t_list **list)
{
	ft_lstdel(list, del);
}
