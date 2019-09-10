/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_singleton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:38:27 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/24 18:35:42 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

t_connection	*get_connection(void)
{
	static t_connection	connection;

	return (&connection);
}

t_hash			*map_dependent_hash(void)
{
	static t_hash	hash[2];

	return (hash);
}
