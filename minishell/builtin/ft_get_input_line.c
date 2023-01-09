/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:16:43 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 19:01:33 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin_header.h"

void	get_input_line(struct s_node *node, int is_in_pipe)
{
	int		fd[2];
	char	*line;
	pid_t	pid;

	(void)is_in_pipe;
	if (!node->parent || !node->parent->left || \
		!node->parent->left->here_doc || pipe(fd) < 0)
		return ;
	line = node->parent->left->here_doc;
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		write(fd[1], line, ft_strlen(line));
		close(fd[1]);
		exit(0);
	}
}
