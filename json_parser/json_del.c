/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:48:01 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/01 17:48:21 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

void		json_del(void *content, size_t size)
{
	t_json	*json;

	(void)size;
	json = (t_json*)content;
	json_destroy(json);
	free(json);
}
