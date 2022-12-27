/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:54:38 by tjo               #+#    #+#             */
/*   Updated: 2022/12/27 18:37:47 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	if (ret == 0)
		return (error_handling("pwd", NULL));
	ft_printf("%s\n", ret);
	free(ret);
	return (0);
}
