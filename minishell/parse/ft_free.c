/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:53:26 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 12:58:51 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(char **tokens)
{
	char	**line;

	line = tokens;
	while (*line)
	{
		free(*line);
		line += 1;
	}
	free(tokens);
}

void	free_tree(struct s_node *node)
{
	struct s_node	*left;
	struct s_node	*right;

	left = node->left;
	right = node->right;
	if (!node->here_doc)
		free(node->here_doc);
	free(node);
	if (left)
		free_tree(left);
	if (right)
		free_tree(right);
}
