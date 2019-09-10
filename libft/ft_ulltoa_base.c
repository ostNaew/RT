/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:58:08 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/12/12 18:51:39 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ulltoa_base(unsigned long long n, const char *base, unsigned nbase)
{
	size_t				size;
	size_t				i;
	unsigned long long	numb;
	char				*res;

	res = NULL;
	if (nbase >= 2 && nbase <= 16)
	{
		numb = n;
		size = 1;
		while (numb / nbase && ++size)
			numb = numb / nbase;
		res = ft_strnew(size);
		numb = n;
		i = 0;
		while ((numb || i == 0) && res)
		{
			res[size - 1 - (i++)] =
				(base ? base : "0123456789ABCDEF")[ABS(numb % nbase)];
			numb = numb / nbase;
		}
	}
	return (res);
}
