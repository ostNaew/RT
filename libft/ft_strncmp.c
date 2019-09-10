/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:53:51 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/27 16:57:20 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	size_t i;

	i = 0;
	if (len == 0)
		return (0);
	while (i < len && s1[i] && s1[i] == s2[i] && s1 != s2)
		++i;
	return (((unsigned char)s1[i == len ? len - 1 : i] -
			(unsigned char)s2[i == len ? len - 1 : i]));
}
