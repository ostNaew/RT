/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_samples_in_task.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:06:39 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 18:07:25 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

size_t	get_num_samples_in_task(void)
{
	return ((8192 - sizeof(t_task_meta)) / sizeof(t_sample) - 1);
}
