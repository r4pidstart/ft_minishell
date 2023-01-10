/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:37:16 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/10 14:10:34 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main_header.h"
#include <readline/history.h>
#include <readline/readline.h>

void	set_signal(void);

static int	show_prompt(char *__cmd)
{
	int		ret;
	size_t	idx;
	char	*cmd;

	ret = 0;
	idx = 0;
	redirect_status(0);
	rl_on_new_line();
	if (!__cmd)
		return (1);
	if (*__cmd == '\0')
		return (0);
	add_history(__cmd);
	cmd = remove_parentheses(__cmd);
	ret = get_tokens(ft_strstrim(__cmd), ret, idx);
	return (ret);
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
		free(cmd);
	}
	free(cmd);
	return (0);
}
