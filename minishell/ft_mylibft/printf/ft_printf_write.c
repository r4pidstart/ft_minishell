/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:53:23 by tjo               #+#    #+#             */
/*   Updated: 2022/09/26 18:54:34 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	write_argument(int flag, char *str, int width)
{
	int	ret;
	int	write_siz;

	ret = 0;
	if (flag & ARG_SHARP && flag & ARG_CAPITAL)
		ret += write(flag >> 16, "0X", 2);
	else if (flag & ARG_SHARP)
		ret += write(flag >> 16, "0x", 2);
	else if (flag & ARG_PLUS)
		ret += write(flag >> 16, "+", 1);
	else if (flag & ARG_SPACE)
		ret += write(flag >> 16, " ", 1);
	else if (flag & FLAG_NEGATIVE)
		ret += write(flag >> 16, "-", 1);
	while (width)
	{
		write_siz = write(flag >> 16, str, width);
		str += write_siz;
		ret += write_siz;
		width -= write_siz;
	}
	return (ret);
}

// the width is processed here
int	write_result(int flag, char *str, int width, int slen)
{
	int			ret;
	char		filler;
	long long	fill_size;

	fill_size = __max(0, width - slen - !!(flag & FLAG_NEGATIVE) \
	- 2 * !!(flag & ARG_SHARP) - !!(flag & ARG_PLUS || flag & ARG_SPACE));
	ret = fill_size;
	filler = ' ';
	if (flag & ARG_ZEROFILL)
	{
		filler = '0';
		if (flag & FLAG_NEGATIVE)
		{
			ret += write(flag >> 16, "-", 1);
			flag &= ~FLAG_NEGATIVE;
		}
	}
	while (!(flag & ARG_LJUSTIFY) && fill_size)
		fill_size -= write(flag >> 16, &filler, 1);
	ret += write_argument(flag, str, slen);
	while (fill_size)
		fill_size -= write(flag >> 16, &filler, 1);
	if (!(flag & FLAG_STRING))
		free(str);
	return (ret);
}
