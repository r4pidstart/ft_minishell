/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:38:57 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/28 15:27:11 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

char	**ft_get_paths(char *envp[])
{
	char			**lines;

	if (!envp)
		return (NULL);
	lines = envp;
	while (*lines)
	{
		if (ft_strncmp(*lines, "PATH", 4) == 0)
			return (ft_split(*lines + 5, ':'));
		lines += 1;
	}
	return (NULL);
}

static char	*ft_get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (ft_strrchr(cmd, '/'))
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (cmd);
}

int	exec_cmd(char *cmd, char **paths, char **envp, int type)
{
	char		*cmd_line;
	char		**cmds;

	cmds = ft_parse(cmd);
	if (!cmds)
		return (1);
	if (envp || *envp)
		return (1);
	cmd_line = ft_get_cmd(paths, *cmds);
	execve(cmd_line, cmds, envp);
	return (1);
}

int	redir(char *cmd, char **paths, char **envp)
{
	int		pipetube[2];
	pid_t	pid;

	if (pipe(pipetube) < 0)
		perror("Invalid pipe");
	pid = fork();
	if (pid)
	{
		close(pipetube[1]);
		dup2(pipetube[0], 0);
		waitpid(pid, NULL, WNOHANG);
		close(pipetube[0]);
	}
	else
	{
		close(pipetube[0]);
		dup2(pipetube[1], 1);
		close(pipetube[1]);
		exit(0);
	}
	return (1);
}
