/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:14:19 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/23 15:24:54 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	size_t	i;

	res = NULL;
	if (s)
	{
		res = ft_strnew(ft_strlen(s));
		i = -1;
		while (s[++i] && res)
			res[i] = f(s[i]);
	}
	return (res);
}
