/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:33:35 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/28 20:47:16 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*res;
	size_t	i;
	char	*limit[2];
	size_t	len;

	i = -1;
	limit[0] = NULL;
	limit[1] = NULL;
	res = NULL;
	if (s)
	{
		len = ft_strlen(s) - 1;
		while (s[++i] && (limit[0] == NULL || limit[1] == NULL))
		{
			if (!ft_isspace(s[i]) && limit[0] == NULL)
				limit[0] = (char *)s + i;
			if (!ft_isspace(s[len - i]) && limit[1] == NULL)
				limit[1] = (char *)s + len - i + 1;
		}
		res = ft_strsub(s, (unsigned)(limit[0] - s), limit[1] - limit[0]);
	}
	return (res);
}
