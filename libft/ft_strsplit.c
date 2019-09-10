/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:39:19 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/27 15:13:01 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static size_t	count_size(char const *s, char c)
{
	size_t size;
	size_t i;

	size = 1;
	i = 0;
	while (s[i] && ++size)
	{
		while (s[i] == c)
			++i;
		while (s[i] && s[i] != c)
			++i;
	}
	return (size);
}

static void		free_array(char ***array)
{
	char **current;

	current = (array ? *array : NULL);
	while (current && *current)
	{
		free((void *)*current);
		++current;
	}
	if (array)
	{
		free((void *)*array);
		*array = NULL;
	}
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	char	*end;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (s && *s == c)
		++s;
	res = s ? (char **)ft_memalloc(sizeof(char *) * count_size(s, c)) : NULL;
	while (res && *s)
	{
		end = ft_strchr(s, c);
		end = (end == NULL) ? (char *)s + ft_strlen(s) : end;
		res[size++] = ft_strsub(s, 0, end - s);
		if (res[size - 1] == NULL)
			free_array(&res);
		s = end;
		while (*s == c)
			++s;
	}
	return (res);
}
