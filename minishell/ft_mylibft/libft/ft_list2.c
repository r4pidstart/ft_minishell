/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:50:06 by tjo               #+#    #+#             */
/*   Updated: 2022/08/30 04:14:22 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./ft_libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ret;

	if (!lst)
		return (0);
	ret = lst;
	while (ret->next)
		ret = ret->next;
	return (ret);
}

static void	free_nodes(t_list *dummy, void (*del)(void *))
{
	t_list	*cur;
	t_list	*tmp;

	cur = dummy->next;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		del(tmp->content);
		free(tmp);
	}
	free(dummy);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dummy;
	t_list	*tmp;
	t_list	*cur;

	dummy = ft_lstnew(NULL);
	if (!dummy)
		return (0);
	cur = dummy;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			free_nodes(dummy, del);
			return (0);
		}
		cur->next = tmp;
		cur = cur->next;
		lst = lst->next;
	}
	cur = dummy->next;
	free(dummy);
	return (cur);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (!ret)
		return (0);
	ret->content = content;
	ret->next = 0;
	return (ret);
}

int	ft_lstsize(t_list *lst)
{
	int		cnt;
	t_list	*cur;

	if (!lst)
		return (0);
	cnt = 0;
	cur = lst;
	while (cur)
	{
		cur = cur->next;
		cnt++;
	}
	return (cnt);
}
