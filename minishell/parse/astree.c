/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:06:49 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 18:45:25 by tjo              ###   ########.fr       */
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
		.line = NULL,
		.right = NULL,
		.left = NULL,
		.type = type,
		.depth = 0,
		.root = root,
		.parent = NULL,
		.here_doc = NULL,
	};
	if (root == NULL)
		node->root = node;
	if (line)
		node->line = ft_strdup(line);
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

static void	__set_node_pipe(struct s_node *node, int *is_in_pipe, int *fd)
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	if (node->type == PIPE && node->root->depth != 0
		&& ((node == node->root) || (node->depth + 1 < node->root->depth)))
		*is_in_pipe = 1;
	node->std_inout[0] = fd[0];
	node->std_inout[1] = fd[1];
}

void	search_tree(struct s_node *node, int *is_in_pipe, int *ret)
{
	int	oldfd[2];

	if (node->type == PIPE || node->type == CMD || node->type == ROOT)
		__set_node_pipe(node, is_in_pipe, oldfd);
	if (node->line)
		*ret = builtin_executer(node, node->line, *is_in_pipe);
	if (*ret && *is_in_pipe && node->type != PIPE)
		exit(1);
	if (node->left && node->type != PIPE)
		search_tree(node->left, is_in_pipe, ret);
	if (node->type == PIPE || node->type == NON_PIPE)
		*is_in_pipe = 0;
	if (node->right && node->type != NON_PIPE)
		search_tree(node->right, is_in_pipe, ret);
	if (node->type == PIPE || node->type == NON_PIPE
		|| node->type == CMD || node->type == ROOT)
	{
		dup2(oldfd[0], 0);
		dup2(oldfd[1], 1);
		close(oldfd[0]);
		close(oldfd[1]);
	}
	if (node->type == CMD)
		do_cmd_token(node, *is_in_pipe, *ret);
}
