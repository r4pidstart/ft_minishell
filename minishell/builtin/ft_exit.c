/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:10:35 by tjo               #+#    #+#             */
/*   Updated: 2022/12/28 20:21:10 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	ft_exit(char **s)
{
	int	tmp;
	int	chk;

	if (s[1] == NULL)
	{
		ft_printf("exit\n");
		exit(1); // ?
	}
	ft_printf("exit\n");
	chk = 0;
	tmp = ft_atoi_check(s[1], &chk);
	if (chk)
		exit(255); // minishell: exit: s[1]: numeric argument required
	else if (s[2] != 0)
		return (1); // minishell: exit: too many arguments
	else
		exit(tmp % 256);
}