/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:52:53 by tjo               #+#    #+#             */
/*   Updated: 2023/01/05 12:34:47 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_main_header.h"

extern char	**environ;

static int	get_fd(char *file, int flag)
{
	int	fd;

	fd = open(file, flag, 0644);
	if (fd < 0)
	{
		free(file);
		return (-1);
	}
	free(file);
	return (fd);
}

char	*get_env_path(void)
{
	static char	*path;

	if (path == 0)
		path = ft_strjoin(getenv("HOME"), ENVP);
	return (path);
}

int	init_envp(void)
{
	int		fd;
	char	**envp;
	char	*path;

	path = ft_strjoin(getenv("HOME"), ENVP);
	if (!path)
		return (1);
	fd = get_fd(path, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
		return (1);
	envp = environ;
	while (*envp)
	{
		write(fd, *envp, ft_strlen(*envp));
		write(fd, "\n", 1);
		envp += 1;
	}
	close(fd);
	return (0);
}

char	**get_envp_ptr(void)
{
	ssize_t	byte;
	char	*ret;
	char	*old;
	int		fd;
	char	*buffer;

	fd = get_fd(ft_strjoin(getenv("HOME"), ENVP), O_RDONLY);
	if (fd < 0)
		return (NULL);
	byte = 0;
	buffer = (char *)malloc(sizeof(*buffer) * (BUF_SIZE + 1));
	ret = ft_strdup("");
	while (ret && buffer)
	{
		byte = read(fd, buffer, BUF_SIZE);
		if (byte <= 0)
			break ;
		buffer[BUF_SIZE] = 0;
		old = ret;
		ret = ft_strjoin(old, buffer);
		free(old);
	}
	close(fd);
	free(buffer);
	return (ft_split(ret, '\n'));
}
