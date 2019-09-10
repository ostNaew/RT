/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:48:33 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/23 16:39:55 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t	size;
	size_t	i;
	long	numb;
	char	*res;

	numb = n;
	i = 0;
	size = n < 0 ? 2 : 1;
	while (numb / 10 && ++size)
		numb = numb / 10;
	res = ft_strnew(size);
	if (n < 0 && res)
		res[0] = '-';
	numb = n < 0 ? -(long)n : (long)n;
	while ((numb || i == 0) && res)
	{
		res[size - 1 - i++] = (numb % 10) + '0';
		numb = numb / 10;
	}
	return (res);
}
