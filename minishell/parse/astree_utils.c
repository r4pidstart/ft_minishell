/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:00:51 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 19:33:24 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

static void	__astree_insert_redir(struct s_node *r, struct s_node *node,
		char *line, char *check)
{
	if (*check)
		;
	if (node->left && !node->right)
	{
		node->right = ft_alloc_node(NULL, REDIRECT, r);
		if (!node->right)
			*check = 1;
		else
			node->right->parent = node;
	}
	if (node->left)
		__astree_insert_redir(r, node->right, line, check);
	else if (!node->left)
	{
		node->left = ft_alloc_node(line, REDIRECT, r);
		if (!node->left)
			*check = 1;
		else
			node->left->parent = node;
		return ;
	}
}

static int	astree_insert_redir(struct s_node *root, char *line)
{
	struct s_node	*node;
	char			check;

	check = 0;
	node = ft_get_cmd_token(root);
	if (!node)
		return (1);
	if (!node->left)
		node->left = ft_alloc_node(NULL, REDIRECTS, root);
	if (!node->left)
		return (1);
	if (!node->left->parent)
		node->left->parent = node;
	__astree_insert_redir(root, node->left, line, &check);
	if (check)
		return (1);
	return (0);
}

static int	astree_insert_scmd(struct s_node *root, char *line)
{
	struct s_node	*node;

	node = ft_get_cmd_token(root);
	if (!node)
		return (1);
	if (node->right)
		return (1);
	node->right = ft_alloc_node(line, SIMPLE_CMD, root);
	node->right->parent = node;
	if (!node->right)
		return (1);
	return (0);
}

static int	astree_insert_pipe(struct s_node *root)
{
	size_t			idx;
	struct s_node	*node;

	idx = 0;
	node = root;
	while (idx++ < root->depth)
		node = node->right;
	if (node->right)
		return (1);
	node->right = ft_alloc_node("|", PIPE, root);
	if (!node->right)
		return (1);
	node->right->parent = node;
	node->right->depth = root->depth;
	root->depth += 1;
	return (0);
}

int	astree_insert_node(struct s_node *root, char *line, char type)
{
	if (type == SIMPLE_CMD)
		return (astree_insert_scmd(root, line));
	if (type == REDIRECT)
		return (astree_insert_redir(root, line));
	if (type == PIPE)
		return (astree_insert_pipe(root));
	return (1);
}
