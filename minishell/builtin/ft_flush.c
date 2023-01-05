/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:35:00 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/05 13:09:40 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin_header.h"

void	ft_flush(void)
{
	int	oldfd[2];
	int	fd;

	oldfd[0] = dup(0);
	oldfd[1] = dup(1);

	fd = open("/dev/null", O_WRONLY);
	if (fd < 0)
	{
		fprintf(stderr, "FUCK\n");
		return ;
	}
	dup2(fd, 0);
	close(fd);
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close(oldfd[0]);
	close(oldfd[0]);
}
