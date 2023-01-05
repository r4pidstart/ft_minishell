/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:49:47 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/05 09:42:17 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_read_file(int fd, char **back_up, char *buffer)
{
	char		*old;
	ssize_t		bytes;

	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
			return (NULL);
		*(buffer + bytes) = '\0';
		if (!*back_up)
			*back_up = ft_strdup("");
		old = *back_up;
		*back_up = ft_strjoin(old, buffer);
		if (!*back_up)
			return (NULL);
		free(old);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*back_up);
}

static char	*ft_get_next_line(char **line)
{
	char	*back;
	char	*ret;

	back = *line;
	while (*back != '\0' && *back != '\n')
		back ++;
	if (!*back)
		return (NULL);
	ret = ft_substr(*line, back - *line + 1, ft_strlen(back + 1));
	*(back + 1) = 0;
	if (!ret)
		return (NULL);
	if (!*ret)
		return (NULL);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*back_up;
	char		*buffer;

	if (fd < 0)
		return (NULL);
	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (buffer);
	line = ft_read_file(fd, &back_up, buffer);
	free(buffer);
	if (!line)
	{
		free(back_up);
		back_up = NULL;
		return (line);
	}
	back_up = ft_get_next_line(&line);
	return (line);
}
