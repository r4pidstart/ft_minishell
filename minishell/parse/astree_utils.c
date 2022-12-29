/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:00:51 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/28 16:15:52 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

static void	__astree_insert_redir(struct s_node *node, char *line, char *check)
{
	if (*check)
		;
	if (node->left && !node->right)
	{
		node->right = ft_alloc_node(NULL, REDIRECT);
		if (!node->right)
			*check = 1;
	}
	if (node->left)
		__astree_insert_redir(node->right, line, check);
	else if (!node->left)
	{
		node->left = ft_alloc_node(line, REDIRECT);
		if (!node->left)
			*check = 1;
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
		node->left = ft_alloc_node(NULL, REDIRECTS);
	if (!node->left)
		return (1);
	__astree_insert_redir(node->left, line, &check);
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
	node->right = ft_alloc_node(line, SIMPLE_CMD);
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
	node->right = ft_alloc_node("|", PIPE);
	if (!node->right)
		return (1);
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
