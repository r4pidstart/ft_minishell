/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:37:16 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 13:42:48 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main_header.h"
#include <readline/history.h>
#include <readline/readline.h>

void	set_signal(void);

static int	__do_cmds(char *cmd)
{
	char	**tokens;
	int		nr_tokens;
	char	*new_cmd;
	int		ret;

	ret = 1;
	new_cmd = line_env_expender(cmd);
	tokens = malloc(sizeof(*tokens) * (ft_strlen(new_cmd) + 1));
	if (!tokens)
		return (1);
	if (!parse_cmd(tokens, new_cmd, &nr_tokens))
		ret = do_cmds(tokens);
	free_tokens(tokens);
	free(new_cmd);
	return (ret);
}

static void	do_tokens(char **cmd)
{
	int		cmd_fail;

	cmd_fail = 1;
	while (*cmd)
	{
		if (ft_strncmp(*cmd, "&&", 3) == 0)
		{
			if (cmd_fail)
				cmd ++;
			cmd ++;
			continue ;
		}
		else if (ft_strncmp(*cmd, "||", 3) == 0)
		{
			if (!cmd_fail)
				cmd ++;
			cmd += 1;
			continue ;
		}
		cmd_fail = __do_cmds(*cmd);
		cmd += 1;
	}
}

static int	show_prompt(char *cmd)
{
	char	**tokens;

	redirect_status(0);
	rl_on_new_line();
	if (!cmd)
		return (1);
	if (*cmd == '\0')
		return (0);
	add_history(cmd);
	cmd = remove_parentheses(cmd);
	tokens = parse_tokens(cmd);
	if (tokens)
	{
		do_tokens(tokens);
		free_tokens(tokens);
	}
	return (0);
}

int	main(void)
{
	char	*cmd;

	if (init_envp())
		return (0);
	set_signal();
	exit_code_export(0);
	while (1)
	{
		cmd = readline(MINISHELL);
		if (!cmd)
			break ;
		if (show_prompt(cmd))
			break ;
	}
	return (0);
}

// segfault when "\"" << solved
// sigint exitcode << solved
// fork exitcode 127 126 << solved
// ambigous redirect << solved
