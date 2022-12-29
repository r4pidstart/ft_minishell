/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:33:52 by tjo               #+#    #+#             */
/*   Updated: 2022/12/29 16:39:29 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	error_handling(char *progname, char *custom_msg, char *path)
{
	ft_fprintf(STDERR_FILENO, "%s: ", progname);
	if (custom_msg)
		ft_fprintf(STDERR_FILENO, "%s", custom_msg);
	else
		ft_fprintf(STDERR_FILENO, "%s", strerror(errno));
	if (path)
		ft_fprintf(STDERR_FILENO, ": %s", path);
	ft_fprintf(STDERR_FILENO, "\n");
	return (errno);
}
