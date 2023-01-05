/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:18:52 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/05 12:14:56 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <stdint.h>

static void	chg_gal(int *is_gal, char *cmd)
{
	if (*is_gal == 0 && (*cmd == '\'' || *cmd == '\"'))
		*is_gal = *cmd;
	else if (*is_gal == *cmd)
		*is_gal = 0;
}

static int	replace_parnthese(int *stack, char *line, char *cmd, int *idx)
{
	if (*cmd == '(')
	{
		stack[*idx] = cmd - line;
		*idx += 1;
	}
	else if (*cmd == ')')
	{
		if (*idx < 1 || stack[*idx - 1] == -1)
		{
			free(stack);
			return (1);
		}
		line[stack[*idx - 1]] = ' ';
		stack[*idx - 1] = -1;
		*cmd = ' ';
		*idx -= 1;
	}
	return (0);
}

static int	*alloc_stack(int lens)
{
	int	*stack;
	int	idx;

	idx = 0;
	stack = (int *)malloc(sizeof(int) * lens);
	if (!stack)
		return (NULL);
	while (idx < lens)
	{
		stack[idx] = -1;
		idx += 1;
	}
	return (stack);
}

static char	*return_value(char *line, int *stack, int is_gal)
{
	int	item;

	item = *stack;
	free(stack);
	if (item != -1 || is_gal != 0)
		return (NULL);
	return (line);
}

char	*remove_parentheses(char *line)
{
	int		*stack;
	int		idx;
	char	*cmd;
	int		is_gal;

	is_gal = 0;
	cmd = line;
	idx = 0;
	if (!line)
		return (NULL);
	stack = alloc_stack(ft_strlen(line));
	if (!stack)
		return (NULL);
	while (*cmd)
	{
		chg_gal(&is_gal, cmd);
		if (is_gal == 0)
		{
			if (replace_parnthese(stack, line, cmd, &idx))
				return (NULL);
		}
		cmd += 1;
	}
	return (return_value(line, stack, is_gal));
}
