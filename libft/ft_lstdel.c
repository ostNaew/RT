/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:29:25 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/27 20:50:55 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *current;

	if (alst && del)
	{
		current = *alst;
		while (current)
		{
			*alst = current->next;
			ft_lstdelone(&current, del);
			current = *alst;
		}
	}
}
