/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:46:28 by tjo               #+#    #+#             */
/*   Updated: 2022/12/29 15:59:31 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static int	make_envlist(t_list **envlist)
{
	char	*tmp;
	int		env_fd;

	env_fd = open(get_env_path(), O_CREAT | O_RDONLY, 0644);
	*envlist = 0;
	while (1)
	{
		tmp = get_next_line(env_fd);
		if (!tmp)
			break ;
		ft_lstadd_back(envlist, ft_lstnew(tmp));
	}
	close(env_fd);
	return (0);
}

static int	free_envlist(t_list *envlist)
{
	t_list	*next;

	while (envlist)
	{
		next = envlist->next;
		free(envlist->content);
		free(envlist);
		envlist = next;
	}
	return (0);
}

int	env(char **s)
{
	t_list	*envlist;
	t_list	*cur;
	int		list_len;
	char	*tmp;

	(void)s;
	make_envlist(&envlist);
	tmp = envlist->content;
	list_len = ft_lstsize(envlist);
	while (list_len > 0)
	{
		cur = envlist;
		while (cur)
		{
			if (ft_strncmp(tmp, cur->content, -1) > 0)
				tmp = cur->content;
			cur = cur->next;
		}
		ft_printf("%s", tmp);
		tmp[0] = 127;
		list_len--;
	}
	free_envlist(envlist);
	return (0);
}
