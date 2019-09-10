/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_lack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:50:54 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/01 17:51:22 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

int	element_lack(char **json_string, int *status, char end)
{
	if (**json_string == ',')
	{
		*json_string += 1;
		skip_spaces(json_string);
		if (**json_string == end)
		{
			*status = -1;
			return (1);
		}
	}
	return (0);
}
