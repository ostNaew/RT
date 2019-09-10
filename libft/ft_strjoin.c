/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:27:55 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/23 15:27:45 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	res = NULL;
	if (s1 && s2)
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		res = ft_strnew(s1_len + s2_len);
		if (res != NULL)
		{
			ft_memcpy(res, s1, s1_len);
			ft_memcpy(res + s1_len, s2, s2_len);
		}
	}
	return (res);
}
