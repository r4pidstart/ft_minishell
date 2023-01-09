/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:16:43 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 14:03:12 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin_header.h"

/*static void	send_eof(int fd, char eof)
{
	write(fd, &eof, 1);
}*/

void	get_input_line(struct s_node *node, int is_in_pipe)
{
	int		fd[2];
	char	*line;
	pid_t	pid;

	is_in_pipe = 0;
	if (!node->root->depth)
		return ;
	if (!node->parent->left)
		return ;
	if (!node->parent->left->here_doc)
		return ;
	if (pipe(fd) <0)
		return ;
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		write(fd[1] ,line, ft_strlen(line));
		close(fd[1]);
		exit(0);
	}
}
