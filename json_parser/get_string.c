/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:19:05 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/13 13:58:18 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

static void	fill_res(char *str, char *res)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '\\')
			res[++j] = ("\"\\/\b\n\r\t")[
						ft_strchr("\"\\/bnrt", str[++i]) - "\"\\/bnrt"];
		else
			res[++j] = str[i];
	}
	free(str);
}

static char	*replace_escape_characters(char *str)
{
	char	*res;
	size_t	i;
	size_t	characters;

	i = -1;
	characters = 0;
	while (str[++i])
	{
		if (str[i] == '\\')
		{
			if (ft_strchr("\"\\/bnrt", str[++i]) != NULL)
				++characters;
			else
			{
				free(str);
				return (NULL);
			}
		}
	}
	res = ft_strnew(ft_strlen(str) - characters);
	fill_res(str, res);
	return (res);
}

char		*get_string(char **json_string)
{
	char	*res;
	char	*tmp;
	size_t	i;
	size_t	len;

	tmp = *json_string;
	len = ft_strlen(tmp);
	i = 0;
	while (++i < len)
		if (tmp[i] == '\\')
			++i;
		else if (tmp[i] == '"')
			break ;
	if (i == len || ft_memchr(tmp, '\n', i) || ft_memchr(tmp, '\r', i) ||
			ft_memchr(tmp, '\b', i) || ft_memchr(tmp, '\f', i) ||
			ft_memchr(tmp, '\t', i))
		return (NULL);
	res = ft_strsub(*json_string, 1, i - 1);
	res = replace_escape_characters(res);
	*json_string += i + 1;
	return (res);
}
