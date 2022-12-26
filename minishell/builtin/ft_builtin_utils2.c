/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:45:45 by tjo               #+#    #+#             */
/*   Updated: 2022/12/26 19:45:53 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	print_all_env(void)
{
	int		env_fd;
	char	*env;

	env_fd = open(ENV_FILE, O_CREAT | O_RDONLY, 0644);
	while (1)
	{
		env = get_next_line(env_fd);
		if (!env)
			return (1);
		ft_printf("%s", env);
		free(env);
	}
	close(env_fd);
}