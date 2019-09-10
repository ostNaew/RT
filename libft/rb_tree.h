/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 16:59:27 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:30:04 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_H
# define RB_TREE_H

# include <stdlib.h>

typedef struct	s_rb_tree
{
	struct s_rb_tree	*left;
	struct s_rb_tree	*right;
	struct s_rb_tree	*parent;
	void				*content;
	size_t				content_size;
	char				black;
}				t_rb_tree;

t_rb_tree		*grandparent(t_rb_tree *node);

#endif
