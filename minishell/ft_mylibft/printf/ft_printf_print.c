/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:38:49 by tjo               #+#    #+#             */
/*   Updated: 2022/09/26 20:30:16 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	print_char(int flag, int width, va_list *vl)
{
	char	*tmp;
	int		fd;

	fd = flag >> 16 << 16;
	tmp = (char *)malloc(sizeof(char) * 2);
	if (!tmp)
		return (0);
	tmp[0] = va_arg(*vl, int);
	tmp[1] = '\0';
	return (write_result((flag & ARG_LJUSTIFY) | fd, tmp, __max(width, 1), 1));
}

int	print_string(int flag, int width, int precision, va_list *vl)
{
	char		*tmp;
	long long	len;
	int			fd;

	fd = flag >> 16 << 16;
	tmp = va_arg(*vl, char *);
	if (!tmp)
		tmp = "(null)";
	len = ft_strlen(tmp);
	if (flag & ARG_PRECISION && len > precision)
		len = precision;
	return (write_result((flag & ARG_LJUSTIFY) | FLAG_STRING | fd, \
	tmp, __max(len, width), len));
}

int	print_pointer(int flag, int width, va_list *vl)
{
	char	*tmp;
	int		len;
	size_t	num;

	num = va_arg(*vl, size_t);
	len = get_length(16, num);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, len, num);
	return (write_result((flag | ARG_SHARP), tmp, __max(len, width), len));
}

int	print_dec(int flag, int width, int precision, va_list *vl)
{
	char		*tmp;
	int			len;
	int			mi;
	long long	num;

	num = va_arg(*vl, int);
	mi = 0;
	if (!(flag & ARG_UNSIGNED) && num < 0)
	{
		mi = 1;
		num = -num;
		flag &= ~(ARG_PLUS | ARG_SPACE);
	}
	if (flag & ARG_ZEROFILL && flag & ARG_PRECISION)
		flag &= ~ARG_ZEROFILL;
	len = __max(get_length(10, (unsigned int)num), precision);
	if (flag & ARG_PRECISION && !precision && !num)
		len = 0;
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_udec(tmp, len, num);
	return (write_result(flag | (mi * FLAG_NEGATIVE), \
	tmp, __max(len, width), len));
}

int	print_hex(int flag, int width, int precision, va_list *vl)
{
	char			*tmp;
	int				len;
	unsigned int	num;

	num = va_arg(*vl, unsigned int);
	if (!num && flag & ARG_SHARP)
		flag -= ARG_SHARP;
	if (flag & ARG_ZEROFILL && flag & ARG_PRECISION)
		flag &= ~ARG_ZEROFILL;
	len = __max(get_length(16, num), precision);
	if (flag & ARG_PRECISION && !precision && !num)
		len = 0;
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, len, num);
	return (write_result(flag, tmp, __max(len, width), len));
}
