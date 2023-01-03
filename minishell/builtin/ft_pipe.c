/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:53:26 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/03 16:55:26 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"ft_builtin_header.h"

int make_pipe(struct s_node *node)
{
	int			fd[2];
	pid_t		pid;

	if (node->root->depth == 0 || node->depth + 1 == node->root->depth)
	{
		node->type = ROOT;
		return (0);
	}
	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0); // WNOHANG);
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
