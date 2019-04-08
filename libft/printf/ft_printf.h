/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 11:44:21 by hvromman          #+#    #+#             */
/*   Updated: 2018/10/27 11:47:06 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <locale.h>
# include <wchar.h>
# include "libft.h"

# define FLAG " +0-#'"
# define MODIFIER "Lhljz"
# define CONVERTER "diuoxXcs%pDUOCSfFgGeEnbr>"

# define NC "\x1b[0m"
# define I "\x1b[3m"
# define U "\x1b[4m"
# define B "\x1b[1m"

# define BLACK "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

# define BBLACK "\x1b[90m"
# define BRED "\x1b[91m"
# define BGREEN "\x1b[92m"
# define BYELLOW "\x1b[93m"
# define BBLUE "\x1b[94m"
# define BMAGENTA "\x1b[95m"
# define BCYAN "\x1b[96m"
# define BWHITE "\x1b[97m"

char	*g_str;
int		g_len;
int		g_output;
char	*g_color;
char	**g_outstr;

int		balise_func(char **fm, int *pos);
int		ft_printf(const char *restrict format, ...);
int		start(char **f, int w[2], char **fm, va_list ap);
int		end(char *f, char **fm);
int		parser(va_list ap, char **fm);
int		go_to_right_func(va_list ap, char *f, int w[2]);

int		int_dispatcher(va_list ap, char *f, int w[2], int pos);
int		oct_dispatcher(va_list ap, char *f, int w[2], int pos);
int		uns_dispatcher(va_list ap, char *f, int w[2], int pos);
int		hex_dispatcher(va_list ap, char *f, int w[2], int pos);
int		mhe_dispatcher(va_list ap, char *f, int w[2], int pos);
int		bin_dispatcher(va_list ap, char *f, int w[2], int pos);
int		num_dispatcher(va_list ap, char *f, int pos);
int		efl_dispatcher(va_list ap, char *f, int w[2], int pos);
int		flo_dispatcher(va_list ap, char *f, int w[2], int pos);
int		gfl_dispatcher(va_list ap, char *f, int w[2], int pos);

int		is_color(char *fm, int *count, char buicolor[19]);
int		change_status(void);

char	*realloc_g_str(int size);
int		trun(int nb);
char	*ft_strljoin(char *first, char *second, int len, int len2);
int		end_conv(char *created, char *flag, int length);
int		end_conv_nothing(int to_return, char *flag, char *new, int size);

int		len_intmax_t(intmax_t n, char f);
void	ft_itoa_u(intmax_t n, char *to_write, int length, char f);
int		signed_func(intmax_t number, char *flag, int width[2]);

int		unsigned_func(uintmax_t number, char *flag, int width[2]);
int		octal_func(uintmax_t number, char *flag, int width[2]);

int		len_hintmax_t(uintmax_t n);
void	ft_hitoa_u(uintmax_t n, char *to_write, int length);
int		hex_func(uintmax_t number, char *flag, int width[2]);
int		mhex_func(uintmax_t number, char *flag, int width[2]);

int		percent_func(char *flag, int width[2]);
int		p_func(uintmax_t number, char *flag, int width[2]);
int		not_correct_flag(char *flag, int width[2]);

int		n_intfunc(int *n, char *flag);
int		n_longfunc(long *n, char *flag);
int		n_longlongfunc(long long *n, char *flag);
int		n_shortfunc(short *n, char *flag);
int		n_charfunc(char *n, char *flag);
int		n_ssizetfunc(ssize_t *n, char *flag);
int		n_intmaxtfunc(intmax_t *n, char *flag);

int		float_func(long double nb, char *flag, int width[2]);
int		exponent(long double *nb, int change);
int		eloat_func(long double nb, char *f, int w[2], int is_upper);
int		gloat_func(long double nb, char *f, int w[2], int is_upper);

int		binary_func(uintmax_t nb, char *f, int w[2]);
int		output_file_func(va_list ap, char *f);

int		char_func(unsigned char c, char *flag, int width[2]);
int		string_func(char *s, char *flag, int width[2], int fr);
int		rtring_func(char *s, char *flag, int width[2]);
int		lchar_func(wint_t c, char *flag, int width[2]);
int		lstring_func(wchar_t *s, char *flag, int width[2]);

#endif
