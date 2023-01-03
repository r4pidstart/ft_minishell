/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:12:47 by tjo               #+#    #+#             */
/*   Updated: 2022/07/30 02:58:02 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	ft_custom_atoi(char **c, int *argu_len)
{
	int			sign;
	long long	ret;

	sign = 1;
	ret = 0;
	if (**c == '+' || **c == '-')
	{
		if (**c == '-')
			sign = -1;
		(*c)++;
	}
	while ('0' <= **c && **c <= '9')
	{
		ret = ret * 10 + (**c) - '0';
		(*c)++;
		(*argu_len)++;
	}
	return (ret * sign);
}

int	parse_precision(char **c, int *precision, va_list *vl, int *argu_len)
{
	int	ret;

	ret = 0;
	*precision = 0;
	if (**c == '.')
		ret = ARG_PRECISION;
	if (ret)
	{
		(*c)++;
		(*argu_len)++;
		if (**c == '*')
		{
			*precision = va_arg(*vl, int);
			(*c)++;
			(*argu_len)++;
		}
		else if ('0' <= **c && **c <= '9')
			*precision = ft_custom_atoi(c, argu_len);
	}
	return (ret);
}

static void	parse_width(char **c, int *width, va_list *vl, int *argu_len)
{
	if (**c == '*')
	{
		(*c)++;
		(*argu_len)++;
		*width = va_arg(*vl, int);
	}
	else if ('0' <= **c && **c <= '9')
		*width = ft_custom_atoi(c, argu_len);
}

int	parse_flag2(char **c, int *width, va_list *vl, int *argu_len)
{
	int	ret;

	ret = 0;
	*width = 0;
	if (**c == '-')
	{
		while (**c == '-')
		{
			(*c)++;
			(*argu_len)++;
		}
		ret = ARG_LJUSTIFY;
	}
	else if (**c == '0')
	{
		(*c)++;
		(*argu_len)++;
		ret = ARG_ZEROFILL;
	}
	parse_width(c, width, vl, argu_len);
	return (ret);
}

int	parse_flag1(char **c, int *argu_len)
{
	int	ret;

	ret = 0;
	if (**c == '#')
		ret = ARG_SHARP;
	else if (**c == '+')
		ret = ARG_PLUS;
	else if (**c == ' ')
		ret = ARG_SPACE;
	if (ret)
	{
		(*c)++;
		(*argu_len)++;
	}
	return (ret);
}
