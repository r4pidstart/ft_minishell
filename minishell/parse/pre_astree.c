/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_astree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:24:27 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 13:26:34 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

struct s_node	*get_near_type_node(struct s_node *node, int type)
{
	struct s_node	*parent;

	parent = node;
	while (node->parent)
	{
		if (node->type == type)
			break ;
		node = node->parent;
	}
	return (node);
}

void	pre_search_tree(struct s_node *node, int *ret)
{
	if (node->type == REDIRECT && ft_strncmp(node->line, "<<", 2) == 0)
		*ret = ft_pre_executer(node->line, node);
	if (node->left)
		pre_search_tree(node->left, ret);
	if (node->right)
		pre_search_tree(node->right, ret);
}
