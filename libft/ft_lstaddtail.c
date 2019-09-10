/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddtail.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 19:34:25 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/01 19:37:25 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddtail(t_list **begin, t_list *new)
{
	t_list	*tmp;

	if (begin)
	{
		tmp = *begin;
		if (!tmp)
		{
			*begin = new;
			return ;
		}
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
