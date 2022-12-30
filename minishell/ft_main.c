/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:37:16 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/30 17:44:11 by tjo              ###   ########.fr       */
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

	dup2(STDIN_FILENO, STDIN_BACKUP);
	dup2(STDOUT_FILENO, STDOUT_BACKUP);
	if (init_envp())
		return (0);
	while (1)
	{
		cmd = readline(MINISHELL);
		rl_on_new_line();
		tokens = malloc(sizeof(*tokens) * (ft_strlen(cmd) + 1));
		if (parse_cmd(tokens, cmd, &nr_tokens))
			break ;
		add_history(cmd);
		do_cmds(tokens);
		dup2(STDIN_BACKUP, STDIN_FILENO);
		dup2(STDOUT_BACKUP, STDOUT_FILENO);
		free(tokens);
	}
	return (0);
}
