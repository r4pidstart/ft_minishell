/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:53:16 by tjo               #+#    #+#             */
/*   Updated: 2023/01/09 23:42:28 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static int	check_already_exist(char *s)
{
	char	*env;
	char	*target;
	int		idx;
	int		ret;

	idx = 0;
	while (s[idx] != '\0' && s[idx] != '=')
		idx++;
	target = ft_substr(s, 0, idx);
	if (!target)
		return (errno = ENOMEM);
	env = get_env(target);
	if (!env)
		return (errno = ENOMEM);
	ret = env[0];
	free(target);
	free(env);
	return (!!ret);
}

static int	write_env(t_list *envlist, int fd, char *target)
{
	t_list	*next;

	while (envlist)
	{
		if (ft_strncmp(envlist->content, target, ft_strlen(target)))
			ft_fprintf(fd, "%s", envlist->content);
		next = envlist->next;
		free(envlist->content);
		free(envlist);
		envlist = next;
	}
	return (0);
}

static int	delete_env(char *s)
{
	int		env_fd;
	t_list	*envlist;
	char	*tmp;

	env_fd = open(get_env_path(), O_CREAT | O_RDONLY, 0644);
	envlist = 0;
	while (1)
	{
		tmp = get_next_line(env_fd);
		if (!tmp)
			break ;
		ft_lstadd_back(&envlist, ft_lstnew(tmp));
	}
	close(env_fd);
	unlink(get_env_path());
	env_fd = open(get_env_path(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
	write_env(envlist, env_fd, s);
	close(env_fd);
	return (0);
}

int	unset(char **s)
{
	int	ret;

	if (s[1] == 0)
		return (0);
	s++;
	while (*s)
	{
		ret = check_already_exist(*s);
		if (ret && ret != 1)
			break ;
		else if (ret)
			delete_env(*s);
		s++;
	}
	if (ret != 1)
		return (ret);
	return (0);
}
