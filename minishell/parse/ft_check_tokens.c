/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:16:53 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/03 10:37:14 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

int	check_pipe(char **lines)
{
	char	**tokens;

	tokens = lines;
	while (*tokens)
	{
		if (**tokens == '|')
		{
			if (!*(tokens + 1) || **(tokens + 1) == '|')
				return (1);
		}
		tokens += 1;
	}
	return (0);
}
