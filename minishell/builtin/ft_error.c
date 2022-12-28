/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:33:52 by tjo               #+#    #+#             */
/*   Updated: 2022/12/28 15:34:38 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	error_handling(char *progname, char *path)
{
	ft_printf("%s: ", progname);
	ft_printf("%s", strerror(errno));
	if (path)
		ft_printf(": %s", path);
	ft_printf("\n");
	return (errno);
}
