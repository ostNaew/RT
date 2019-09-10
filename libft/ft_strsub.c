/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:34:56 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/28 17:07:33 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	sindex;
	char	*res;

	sindex = (size_t)start;
	i = -1;
	res = ft_strnew(len);
	if (res && s)
		ft_memcpy(res, s + sindex, len);
	return (res);
}
