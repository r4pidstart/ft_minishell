/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:41:41 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 16:45:17 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static char	*find_path(char *target)
{
	int		idx;
	char	**paths;
	char	*tmp[3];

	paths = ft_split(get_env("PATH"), ':');
	if (!paths)
		return (0);
	idx = 0;
	tmp[2] = 0;
	while (paths[idx])
	{
		tmp[0] = ft_strjoin(paths[idx], "/");
		tmp[1] = ft_strjoin(tmp[0], target);
		if (access(tmp[1], X_OK) == 0 && !tmp[2])
			tmp[2] = ft_strdup(tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		free(paths[idx++]);
	}
	free(paths);
	return (tmp[2]);
}

static void	exec(char **args, char **envp)
{
	char	*tmp;

	tmp = find_path(args[0]);
	if (access(args[0], F_OK) && (!tmp || access(tmp, F_OK)))
	{
		error_handling("minishell", args[0], "command not found");
		exit(127);
	}
	if (access(args[0], X_OK) == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			error_handling("minishell", 0, args[0]);
			exit(126);
		}
	}
	free(args[0]);
	args[0] = ft_strdup(tmp);
	if (access(args[0], X_OK) || execve(args[0], args, envp) == -1)
	{
		error_handling("minishell", 0, args[0]);
		exit(126);
	}
	exit(1);
}

int	fork_execve(char **parsed)
{
	char	**envp;
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		envp = get_envp_ptr();
		exec(parsed, envp);
	}
	waitpid(pid, &ret, 0);
	return (WEXITSTATUS(ret));
}

int	non_fork_execve(char **parsed)
{
	char	**envp;

	envp = get_envp_ptr();
	exec(parsed, envp);
	return (1);
}
