/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:32:55 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/04 15:07:05 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main_header.h"
#include <readline/history.h>
#include <readline/readline.h>

void	set_signal(void);

static void	signal_handler(int signo)
{
	pid_t	pid;

	set_signal();
	pid = waitpid(-1, NULL, WNOHANG);
	if (signo == SIGINT)
	{
		rl_redisplay();
		rl_replace_line("", 0);
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
}

void	set_signal(void)
{
	struct sigaction	new;
	struct sigaction	old;

	new.sa_handler = signal_handler;
	sigemptyset(&new.sa_mask);
	sigaction(SIGINT, &new, &old);
	sigaction(SIGQUIT, &new, &old);
	sigaction(SIGTERM, &new, &old);
}
