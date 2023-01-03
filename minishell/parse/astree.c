/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:06:49 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/03 10:30:54 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

struct s_node	*ft_alloc_node(char *line, char type, struct s_node *root)
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
		.root = root,
	};
	if (root == NULL)
		node->root = node;
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
		node->left = ft_alloc_node(NULL, CMD, root);
		if (!node->left)
			return (NULL);
	}
	return (node->left);
}

void	search_tree(struct s_node *node, int *is_in_pipe)
{
	int	oldfd[2];

	if (node->type == PIPE || node->type == CMD)
	{
		oldfd[0] = dup(0);
		oldfd[1] = dup(1);
		if (node->type == PIPE && node->root->depth != 0 && ((node == node->root)
			|| (node->depth + 1 < node->root->depth)))
			*is_in_pipe = 1;
	}
	if (node->line)
	{
		fprintf(stderr, "%s [%d]\n",node->line, *is_in_pipe);
		if (builtin_executer(node, node->line, *is_in_pipe))
			return ;
	}
	if (node->left && node->type != PIPE)
		search_tree(node->left, is_in_pipe);
	if (node->type == PIPE || node->type == NON_PIPE)
		*is_in_pipe = 0;
	if (node->right && node->type != NON_PIPE)
		search_tree(node->right, is_in_pipe);
	if (node->type == PIPE || node->type == NON_PIPE || node->type == CMD)
	{
		dup2(oldfd[0], 0);
		dup2(oldfd[1], 1);
	}
}
