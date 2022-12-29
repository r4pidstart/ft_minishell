/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:37:16 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/29 14:37:55 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "types.h"
#include <readline/history.h>

int	main()
{
	char	*cmd;
	char	**tokens;
	int		nr_tokens;

	if (init_envp())
		return (0);
	while (1)
	{
		cmd = readline(MINISHELL);
		tokens = malloc(sizeof(*tokens) * (ft_strlen(cmd) + 1));
		if (parse_cmd(tokens, cmd, &nr_tokens))
			break ;
		do_cmds(tokens);
		free(tokens);
	}
	return (0);
}
