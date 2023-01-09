/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:25:55 by tjo               #+#    #+#             */
/*   Updated: 2023/01/05 09:37:34 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

static t_fd_list	*find_fd(int fd, t_fd_list **lst)
{
	t_fd_list	*ret;

	ret = *lst;
	while (ret)
	{
		if (ret->fd == fd)
			return (ret);
		ret = ret->next;
	}
	ret = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!ret)
		return (0);
	ret->fd = fd;
	ret->next = *lst;
	ret->string = (char *)malloc(sizeof(char) * 1);
	if (!ret->string)
		return (0);
	ret->string[0] = '\0';
	ret->idx = 0;
	return (*lst = ret);
}

static char	*delete_fd(int fd, t_fd_list **lst)
{
	t_fd_list	*tmp;
	t_fd_list	*cur;

	tmp = *lst;
	if (tmp->fd == fd)
	{
		*lst = tmp->next;
	}
	else
	{	
		cur = *lst;
		while (cur->next->fd != fd)
			cur = cur->next;
		tmp = cur->next;
		cur->next = tmp->next;
	}
	free(tmp->string);
	free(tmp);
	return (0);
}

static char	*make_next_string(t_fd_list *node, t_fd_list **lst)
{
	char	*ret;
	char	*tmp;

	if (node->string[node->idx] == '\n')
	{
		ret = ft_custom_substr(node->string, 0, node->idx + 1);
		if (!ret)
			return (0);
		tmp = ft_custom_substr(node->string, node->idx + 1, (size_t)(-1));
		if (!tmp)
			return (0);
		free(node->string);
		node->string = tmp;
		node->idx = 0;
	}
	else
	{
		ret = ft_custom_substr(node->string, 0, node->idx + 1);
		if (!ret)
			return (0);
		delete_fd(node->fd, lst);
	}
	return (ret);
}

static char	*read_next_string(t_fd_list *node, t_fd_list **lst)
{
	char	buf[BUFFER_SIZE];
	int		rd_siz;
	int		len;

	rd_siz = read(node->fd, buf, BUFFER_SIZE);
	if (rd_siz < 0)
		return (0);
	if (rd_siz == 0)
	{
		while (node->string[node->idx] && node->string[node->idx + 1] != '\0' \
		&& node->string[node->idx] != '\n')
			node->idx++;
		return (make_next_string(node, lst));
	}
	node->string = ft_custom_strjoin(node->string, buf, rd_siz);
	if (!node->string)
		return (0);
	len = node->idx + rd_siz;
	while (node->idx < len && \
	node->string[node->idx] != '\0' && node->string[node->idx] != '\n')
		node->idx++;
	if (node->idx == len)
		return (read_next_string(node, lst));
	return (make_next_string(node, lst));
}

char	*get_next_line(int fd)
{
	static t_fd_list	*lst;
	t_fd_list			*node;
	char				*ret;

	node = find_fd(fd, &lst);
	if (!node || node->idx < 0)
		return (0);
	if (read(node->fd, 0, 0) < 0)
		return (delete_fd(fd, &lst));
	ret = read_next_string(node, &lst);
	if (ret && ret[0])
		return (ret);
	if (ret)
		free(ret);
	return (0);
}
