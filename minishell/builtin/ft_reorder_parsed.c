/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reorder_parsed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:44:20 by tjo               #+#    #+#             */
/*   Updated: 2023/01/10 00:43:41 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static size_t	count_lst(t_list *lst)
{
	size_t	ret;
	char	**cur;

	ret = 0;
	while (lst)
	{
		cur = (char **)lst->content;
		if (*cur == 0)
			ret++;
		while (*cur)
		{
			ret++;
			cur++;
		}
		lst = lst->next;
	}
	return (ret);
}

static char	**extract_lst(t_list *lst, size_t len)
{
	char	**ret;
	size_t	idx;
	char	**cur;
	t_list	*next;

	ret = (char **)malloc(sizeof(char *) * (len + 1));
	idx = 0;
	while (lst)
	{
		cur = (char **)lst->content;
		if (*cur == 0)
			ret[idx++] = dummy_string();
		while (*cur)
		{
			ret[idx++] = ft_strdup(*cur);
			free(*cur);
			cur++;
		}
		next = lst->next;
		free(lst->content);
		free(lst);
		lst = next;
	}
	ret[idx] = 0;
	return (ret);
}

int	reorder_parsed(char ***parsed)
{
	char	**new;
	char	**cur;
	t_list	*lst;

	lst = 0;
	cur = *parsed;
	while (*cur)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_split(*cur, (char)7)));
		cur++;
	}
	new = extract_lst(lst, count_lst(lst));
	free_parsed(*parsed);
	*parsed = new;
	return (0);
}
