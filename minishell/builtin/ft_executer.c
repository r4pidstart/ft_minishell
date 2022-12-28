/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:52:15 by tjo               #+#    #+#             */
/*   Updated: 2022/12/28 16:43:05 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static void	select_builtin_func(char *s, int (**func)(char **))
{
	if (ft_strncmp(s, "echo", 5) == 0)
		*func = &echo;
	else if (ft_strncmp(s, "cd", 3) == 0)
		*func = &cd;
	else if (ft_strncmp(s, "pwd", 4) == 0)
		*func = &pwd;
	else if (ft_strncmp(s, "export", 7) == 0)
		*func = &export;
	else if (ft_strncmp(s, "unset", 6) == 0)
		*func = &unset;
	else if (ft_strncmp(s, "env", 4) == 0)
		*func = &env;
	else if (ft_strncmp(s, "exit", 5) == 0)
		*func = &exit;
	else
		*func = NULL;
}

int	builtin_executer(char *s)
{
	char	**parsed;
	char	**ptr;
	int		ret;
	int		(*func)(char **);

	parsed = quote_parser(s);
	select_builtin_func(parsed[0], &func);
	if (func)
		ret = func(parsed);
	ptr = parsed;
	while (*ptr)
		free(*(ptr++));
	free(parsed);
	if (!func)
		return (1); // no matching function
	return (ret);
}

#include<stdio.h>
#include<string.h>
int main(void)
{
	// export("export");
	while(1)
	{
		char test[100000];
		scanf(" %[^\n]", test);
		builtin_executer(test);
		//pwd();
		//system("leaks test");
	}
}