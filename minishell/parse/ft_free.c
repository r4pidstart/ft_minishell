/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:53:26 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/28 15:22:38 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(struct s_node *node)
{
	struct s_node	*left;
	struct s_node	*right;

	left = node->left;
	right = node->right;
	free(node);
	if (left)
		free_tree(left);
	if (right)
		free_tree(right);
}
