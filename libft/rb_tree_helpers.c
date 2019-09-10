/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 17:02:11 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:30:18 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

t_rb_tree	*rb_grandparent(t_rb_tree *node)
{
	if (node && node->parent)
		return (node->parent->parent);
	return (NULL);
}

t_rb_tree	*rb_uncle(t_rb_tree *node)
{
	t_rb_tree	*grandparent;

	if ((grandparent = rb_grandparent(node)))
	{
		if (grandparent->left == node)
			return (grandparent->right);
		else
			return (grandparent->left);
	}
	return (NULL);
}
