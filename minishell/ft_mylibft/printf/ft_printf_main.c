/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:56:30 by tjo               #+#    #+#             */
/*   Updated: 2022/10/01 17:37:51 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

/* cspdiuxX% */
static int	parse_argument(char *c, va_list *vl, int *argu_len, int fd)
{
	int	flag;
	int	width;
	int	precision;

	flag = fd << 16;
	while (*c == '#' || *c == '+' || *c == ' ')
		flag |= parse_flag1(&c, argu_len);
	flag |= parse_flag2(&c, &width, vl, argu_len);
	flag |= parse_precision(&c, &precision, vl, argu_len);
	if (*c == 'c')
		return (print_char(flag, width, vl));
	else if (*c == 's')
		return (print_string(flag, width, precision, vl));
	else if (*c == 'p')
		return (print_pointer(flag, width, vl));
	else if (*c == 'd' || *c == 'i' || *c == 'u')
		return (print_dec(flag | (*c == 'u') * ARG_UNSIGNED, \
		width, precision, vl));
	else if (*c == 'x' || *c == 'X')
		return (print_hex(flag | (*c == 'X') * ARG_CAPITAL, \
		width, precision, vl));
	else if (*c == '%')
		return (write(fd, "%", 1));
	return (0);
}

static int	parse_string(char **cur, va_list *vl, int fd)
{
	int	argu_len;
	int	ret;

	ret = 0;
	argu_len = 1;
	ret = parse_argument(++(*cur), vl, &argu_len, fd);
	(*cur) += argu_len;
	return (ret);
}

int	ft_vfprintf(int fd, const char *str, va_list *vl)
{
	char	*cur;
	int		ret;
	int		cnt;

	cnt = 0;
	cur = (char *)str;
	while (*cur)
	{
		if (*cur == '%')
			cnt += parse_string(&cur, vl, fd);
		else
		{
			ret = write(fd, cur++, 1);
			cnt++;
			if (!ret)
				return (0);
		}
	}
	return (cnt);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	vl;
	int		ret;

	va_start(vl, str);
	ret = ft_vfprintf(fd, str, &vl);
	va_end(vl);
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	va_list	vl;
	int		ret;

	va_start(vl, str);
	ret = ft_vfprintf(1, str, &vl);
	va_end(vl);
	return (ret);
}
