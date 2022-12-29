/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:06:49 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/29 16:02:01 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

struct s_node	*ft_alloc_node(char *line, char type)
{
	struct s_node	*node;

	node = (struct s_node *)malloc(sizeof(*node));
	if (!node)
		return (node);
	*node = (struct s_node){
		.line = line,
		.right = NULL,
		.left = NULL,
		.type = type,
		.depth = 0,
	};
	return (node);
}

void	astree_init(struct s_node *root)
{
	ft_bzero(root, sizeof(*root));
	root->type = ROOT;
	return ;
}

struct s_node	*ft_get_cmd_token(struct s_node *root)
{
	size_t			idx;
	struct s_node	*node;

	idx = 0;
	node = root;
	while (idx++ < root->depth)
		node = node->right;
	if (!node->left)
	{
		node->left = ft_alloc_node(NULL, CMD);
		if (!node->left)
			return (NULL);
	}
	return (node->left);
}

void	search_tree(struct s_node *node)
{
	if (node->line)
		builtin_executer(node->line);
		//printf("[%s]\n", node->line);
	if (node->left)
		search_tree(node->left);
	if (node->right)
		search_tree(node->right);
}
