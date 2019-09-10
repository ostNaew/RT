/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:45:56 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:29:09 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa_base(long long n, const char *base, unsigned nbase)
{
	size_t		size;
	size_t		i;
	long long	numb;
	char		*res;

	res = NULL;
	if (nbase >= 2 && nbase <= 16)
	{
		numb = n;
		size = n < 0 ? 2 : 1;
		while (numb / nbase && ++size)
			numb = numb / nbase;
		res = ft_strnew(size);
		if (n < 0 && res)
			res[0] = '-';
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
