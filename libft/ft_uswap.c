/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:30:27 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:30:28 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_1byte(void *e1, void *e2)
{
	char buf;

	buf = *((char*)e1);
	*((char*)e1) = *((char*)e2);
	*((char*)e2) = buf;
}

static void	swap_2byte(void *e1, void *e2)
{
	short buf;

	buf = *((short*)e1);
	*((short*)e1) = *((short*)e2);
	*((short*)e2) = buf;
}

static void	swap_4byte(void *e1, void *e2)
{
	int buf;

	buf = *((int*)e1);
	((int*)e1)[0] = ((int*)e2)[0];
	((int*)e2)[0] = buf;
}

static void	swap_8byte(void *e1, void *e2)
{
	long buf;

	buf = *((long*)e1);
	*((long*)e1) = *((long*)e2);
	*((long*)e2) = buf;
}

void		ft_uswap(void *e1, void *e2, size_t size)
{
	char buf[size <= 512 ? size : 0];
	char *abuf;

	if (e1 == e2)
		return ;
	if (size == 1 || size == 2 || size == 4 || size == 8)
	{
		if (size == 1)
			swap_1byte(e1, e2);
		if (size == 2)
			swap_2byte(e1, e2);
		if (size == 4)
			swap_4byte(e1, e2);
		if (size == 8)
			swap_8byte(e1, e2);
		return ;
	}
	abuf = size > 512 ? (char *)malloc(size) : NULL;
	if (e1 && e2)
	{
		ft_memcpy((void *)(abuf ? abuf : buf), e1, size);
		ft_memcpy(e1, e2, size);
		ft_memcpy(e2, (void *)(abuf ? abuf : buf), size);
	}
	free(abuf);
}
