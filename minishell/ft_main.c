/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:37:16 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/29 15:51:36 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main_header.h"
#include <readline/history.h>
#include <readline/readline.h>

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
