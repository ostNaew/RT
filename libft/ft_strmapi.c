/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:47:47 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/23 15:24:36 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned	i;
	char		*res;

	i = -1;
	res = NULL;
	if (s)
	{
		res = (char *)ft_strnew(ft_strlen(s));
		while (s[++i] && res)
			res[i] = f(i, s[i]);
	}
	return (res);
}
