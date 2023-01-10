/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:53:26 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/10 14:41:21 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static int	is_redirect_after(struct s_node *node)
{
	if (!node->right)
		return (1);
	if (!node->right->left)
		return (1);
	if (!node->right->left->left)
		return (1);
	if (node->right->left->left->here_doc)
		return (0);
	return (1);
}

static int	__make_pipe(struct s_node *node, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid)
	{
		close(fd[1]);
		if (is_redirect_after(node))
		{
			dup2(fd[0], 0);
		}
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		node->type = NON_PIPE;
		close(fd[1]);
	}
	return (0);
}

int	make_pipe(struct s_node *node)
{
	int			fd[2];

	if (node->root->depth == 0 || node->depth + 1 == node->root->depth)
	{
		node->type = ROOT;
		return (0);
	}
	pipe(fd);
	return (__make_pipe(node, fd));
}
