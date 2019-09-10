/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:31:38 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:04 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_4x4matrix	identity_matrix(void)
{
	t_4x4matrix res;
	unsigned	i;
	unsigned	j;

	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4)
			res.value[i][j] = 0.;
	res.value[0][0] = 1.;
	res.value[1][1] = 1.;
	res.value[2][2] = 1.;
	res.value[3][3] = 1.;
	return (res);
}
