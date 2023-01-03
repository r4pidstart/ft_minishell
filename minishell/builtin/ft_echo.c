/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:43:53 by tjo               #+#    #+#             */
/*   Updated: 2023/01/02 09:51:13 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	echo(char **s)
{
	int	option;

	s++;
	option = 0;
	if ((*s) && ft_strncmp(*s, "-n", 3) == 0)
	{
		option = 1;
		s++;
	}
	while (*s)
	{
		ft_printf("%s", *s);
		s++;
		if (*s)
			ft_printf(" ");
	}
	if (!option)
		ft_printf("\n");
	return (0);
}
