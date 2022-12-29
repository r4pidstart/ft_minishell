/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:10:35 by tjo               #+#    #+#             */
/*   Updated: 2022/12/29 16:34:48 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	ft_exit(char **s)
{
	int	tmp;
	int	chk;

	ft_printf("exit\n");
	if (s[1] == NULL)
		exit(1);
	chk = 0;
	tmp = ft_atoi_check(s[1], &chk);
	if (chk)
	{
		error_handling("minishell: exit", \
			ft_strjoin(s[1], ": numeric argument required"), 0);
		exit(255);
	}
	else if (s[2] != 0)
	{
		error_handling("minishell: exit", "too many arguments", 0);
		return (1);
	}
	else
		exit(tmp % 256);
}