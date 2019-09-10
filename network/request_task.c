/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_task.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:03:02 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 15:12:54 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

void	request_task(dyad_Stream *master)
{
	char	data[sizeof("get_task") - 1 + sizeof(t_hash) * 2 + sizeof(t_nonce)];
	t_hash	hash;
	t_hash	*map_dependent;
	t_nonce	nonce;

	data[0] = 0;
	ft_strcat(data, "get_task");
	nonce = get_nonce();
	ft_memcpy((void*)(data + sizeof("get_task") - 1),
			(void*)&nonce, sizeof(t_nonce));
	map_dependent = map_dependent_hash();
	hash = siphash24((void*)data, sizeof("get_task") - 1 + sizeof(t_nonce),
			(char*)map_dependent);
	ft_memcpy((void*)(data + sizeof("get_task") - 1 + sizeof(t_nonce)),
			(void*)&hash, sizeof(t_hash));
	hash = siphash24((void*)data,
			sizeof("get_task") - 1 + sizeof(t_nonce) + sizeof(t_hash),
			HASH_KEY);
	ft_memcpy((void*)
			(data + sizeof("get_task") - 1 + sizeof(t_nonce) + sizeof(t_hash)),
			(void*)&hash, sizeof(t_hash));
	dyad_write(master, (void*)data, sizeof(data));
}
