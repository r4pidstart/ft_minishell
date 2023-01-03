/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:17:22 by tjo               #+#    #+#             */
/*   Updated: 2023/01/03 16:43:45 by joowpark         ###   ########.fr       */
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

	if (access(args[0], X_OK) == 0)
		if (execve(args[0], args, envp) == -1)
			exit(error_handling("minishell: execve", 0, args[0]));
	//exit(error_handling("minishell: ", "command not found", args[0]));
	tmp = find_path(args[0]);
	if (!tmp)
		exit(error_handling("minishell", args[0], "command not found")); //
		//exit(error_handling("minishell: execve", 0, args[0]));
	free(args[0]);
	args[0] = ft_strdup(tmp);
	if (access(args[0], X_OK) == 0)
		if (execve(args[0], args, envp) == -1)
			exit(error_handling("execve", 0, 0));
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
