/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:37:16 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/04 02:32:33 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main_header.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	set_signal(void);

static void	signal_handler(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	set_signal();
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		if (pid == -1)
		{
			ft_printf("\n");
			write(1, MINISHELL, 12);
		}
		else
			ft_printf("\n");
	}
	if (signo == SIGTERM)
		exit(0);
	else if (signo == SIGQUIT)
		return ;
}

static void	set_signal(void)
{
	struct sigaction	new;
	struct sigaction	old;

	new.sa_handler = signal_handler;
	sigemptyset(&new.sa_mask);
	sigaction(SIGINT, &new, &old);
	sigaction(SIGQUIT, &new, &old);
	sigaction(SIGTERM, &new, &old);
}

static int	show_prompt(char *cmd)
{
	char	**tokens;
	int		nr_tokens;
	char	*new_cmd;

	redirect_status(0);
	rl_on_new_line();
	if (!cmd)
		return (1);
	if (*cmd == '\0')
		return (0);
	add_history(cmd);
	new_cmd = line_env_expender(cmd);
	free(cmd);
	tokens = malloc(sizeof(*tokens) * (ft_strlen(new_cmd) + 1));
	if (!tokens)
		return (1);
	if (!parse_cmd(tokens, new_cmd, &nr_tokens))
		do_cmds(tokens);
	free_tokens(tokens);
	free(new_cmd);
	// system("leaks --list -- $PPID");
	return (0);
}

int	main(void)
{
	char	*cmd;

	if (init_envp())
		return (0);
	set_signal();
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

/*
minishell: ls >>>>> a
minishell: : syntax error near unexpected token : \n
minishell: : syntax error near unexpected token : \n
minishell: : syntax error near unexpected token : \n

minishell: echo '$HOME' "$HOME"
/Users/jotaesik /Users/jotaesik
*/