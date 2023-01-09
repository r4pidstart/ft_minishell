/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_astree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:24:27 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 19:00:45 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

struct s_node	*get_near_type_node(struct s_node *node, int type)
{
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
	if (node->type == REDIRECT && node->line \
		&& ft_strncmp(node->line, "<<", 2) == 0)
		*ret = ft_pre_executer(node->line, node);
	if (node->left)
		pre_search_tree(node->left, ret);
	if (node->right)
		pre_search_tree(node->right, ret);
}
