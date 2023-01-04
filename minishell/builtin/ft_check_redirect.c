/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:46:33 by tjo               #+#    #+#             */
/*   Updated: 2023/01/04 18:55:02 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	check_redirect(char **parsed)
{
	size_t	cnt;
	char	**cur;

	cur = parsed;
	cnt = 0;
	while (*cur)
	{
		cnt++;
		cur++;
	}
	if (cnt > 2)
	{
		redirect_status(1);
		error_handling("minishell", "ambigous redirect", 0);
		return (0);
	}
	return (make_redirection(parsed));
}
