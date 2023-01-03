/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:55:51 by tjo               #+#    #+#             */
/*   Updated: 2022/10/01 17:37:58 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<stdarg.h>
# include<unistd.h>
# include<stdlib.h>
# include"../libft/ft_libft.h"

enum	e_args
{
	ARG_LJUSTIFY = 1 << 1,
	ARG_ZEROFILL = 1 << 2,
	ARG_SHARP = 1 << 3,
	ARG_PLUS = 1 << 4,
	ARG_SPACE = 1 << 5,
	ARG_PRECISION = 1 << 6,
	ARG_CAPITAL = 1 << 7,
	ARG_UNSIGNED = 1 << 8,
	FLAG_NEGATIVE = 1 << 9,
	FLAG_STRING = 1 << 10
};

/* ft_printf_main.c */
int		ft_printf(const char *str, ...);
int		ft_fprintf(int fd, const char *str, ...);
int		ft_vfprintf(int fd, const char *str, va_list *vl);

/* ft_printf_parse.c */
int		parse_flag1(char **c, int *argu_len);
int		parse_flag2(char **c, int *width, va_list *vl, int *argu_len);
int		parse_precision(char **c, int *precision, va_list *vl, int *argu_len);

/* ft_printf_print.c */
int		print_char(int flag, int width, va_list *vl);
int		print_string(int flag, int width, int precision, va_list *vl);
int		print_pointer(int flag, int width, va_list *vl);
int		print_dec(int flag, int width, int precision, va_list *vl);
int		print_hex(int flag, int width, int precision, va_list *vl);

/* ft_printf_utils.c */
// size_t	ft_strlen(const char *s);
int		__max(int a, int b);
int		get_length(int base, size_t n);
void	custom_atoi_udec(char *tmp, int len, unsigned int num);
void	custom_atoi_hex(int flag, char *tmp, int len, size_t n);

/* ft_printf_write.c */
int		write_result(int flag, char *str, int width, int slen);

#endif