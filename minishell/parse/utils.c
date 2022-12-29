/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:42:08 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/29 15:57:34 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

char	*get_envp(char *line, char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(line, *envp, ft_strlen(line)) == 0)
			return (*envp + ft_strlen(line));
	}
	return (NULL);
}
