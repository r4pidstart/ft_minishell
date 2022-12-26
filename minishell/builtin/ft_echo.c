/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:43:53 by tjo               #+#    #+#             */
/*   Updated: 2022/12/26 17:46:57 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	echo(char *s)
{
	size_t	slen;
	int		option_n;

	slen = ft_strlen(s);
	option_n = 0;
	if (slen > 6 && s[5] == '-' && s[6] == 'n' && (s[7] == '\n' || s[7] == ' '))
		option_n = 1;
	s += 5 + option_n * 3;
	slen -= 5 + option_n * 3;
	while (slen)
	{
		ft_printf("%s", s);
	}
	if (!option_n)
		ft_printf("\n");
	return (0);
}
