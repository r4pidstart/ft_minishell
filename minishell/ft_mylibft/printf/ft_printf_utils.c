/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 01:12:41 by tjo               #+#    #+#             */
/*   Updated: 2022/09/12 00:24:56 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	__max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	get_length(int base, size_t n)
{
	int	ret;

	ret = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		ret++;
		n /= base;
	}
	return (ret);
}

void	custom_atoi_udec(char *tmp, int len, unsigned int num)
{
	tmp[len] = '\0';
	while (len--)
	{
		if (!num)
			tmp[len] = '0';
		else
		{
			tmp[len] = num % 10 + '0';
			num /= 10;
		}
	}
}

void	custom_atoi_hex(int flag, char *tmp, int len, size_t num)
{
	tmp[len] = '\0';
	while (len--)
	{
		if (!num)
			tmp[len] = '0';
		else
		{
			if (num % 16 > 9 && flag & ARG_CAPITAL)
				tmp[len] = "ABCDEF"[num % 16 - 10];
			else if (num % 16 > 9)
				tmp[len] = "abcdef"[num % 16 - 10];
			else
				tmp[len] = num % 16 + '0';
			num /= 16;
		}
	}
}
