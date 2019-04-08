/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:42:10 by hvromman          #+#    #+#             */
/*   Updated: 2018/11/04 14:42:14 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_fitoa_u(double n, char *to_write, int length)
{
	int		count_pos;

	count_pos = 0;
	to_write[-1] = '.';
	if (!length)
		return ;
	if (n < 0)
		n *= -1;
	while (count_pos < length)
	{
		n -= (intmax_t)n;
		n *= 10;
		if (count_pos == length - 1 && ((int)(n * 10 + 1e-9) % 10) > 4)
			n += 1;
		to_write[count_pos++] = (int)(n + 1e-9) % 10 + 48;
	}
}

int		float_func(long double nb, char *f, int w[2])
{
	int			small_len;
	int			len;
	int			sln;
	int			size;
	char		*created;

	if (w[1] == -1)
		w[1] = 6;
	small_len = len_intmax_t((intmax_t)nb, f[5]);
	len = small_len + w[1] + (w[1] || f[4] ? 1 : 0);
	sln = len + (nb < 0 || f[0] || f[1] ? 1 : 0);
	size = ft_max(sln, w[0]);
	if (!(created = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	if (nb < 0)
		created[0] = '-';
	else if (f[0] || f[1])
		created[0] = f[1] ? '+' : ' ';
	ft_itoa_u((intmax_t)nb, created + sln - len, small_len, f[5]);
	ft_fitoa_u(nb, created + small_len + sln - len + 1, w[1]);
	if (w[0] == size && !f[3] && ft_memrcpy(created + size - sln, created, sln))
		ft_memset(created, f[2] ? '0' : ' ', size - sln);
	else if (w[0] == size && f[3])
		ft_memset(created + sln, ' ', sln);
	return (end_conv_nothing(0, f, created, size));
}

int		exponent(long double *nb, int change)
{
	int			sign;
	int			exp;
	long double	new;

	new = *nb;
	sign = 1;
	if (new < 0 && (sign = -1))
		new *= -1;
	exp = 0;
	if (new < 1)
		while (new < 1)
		{
			exp--;
			new *= 10;
		}
	else if (new >= 10)
		while (new >= 10)
		{
			exp++;
			new /= 10;
		}
	if (change)
		*nb = new * sign;
	return (exp);
}

void	ft_exp_u(char *to_write, int exp, int is_upper)
{
	to_write[0] = is_upper ? 'E' : 'e';
	to_write[1] = exp < 0 ? '-' : '+';
	if (exp < 0)
		exp *= -1;
	to_write[2] = exp / 10 + '0';
	to_write[3] = exp % 10 + '0';
}

int		eloat_func(long double nb, char *f, int w[2], int is_upper)
{
	int			exp;
	int			len;
	int			sln;
	int			size;
	char		*created;

	w[1] = w[1] == -1 ? 6 : w[1];
	exp = exponent(&nb, 1);
	len = 1 + w[1] + (w[1] || f[4] ? 1 : 0) + 4;
	sln = len + (nb < 0 || f[0] || f[1] ? 1 : 0);
	size = ft_max(sln, w[0]);
	if (!(created = realloc_g_str(size * f[9])))
		return (end_conv_nothing(-1, f, NULL, 0));
	if (nb < 0)
		created[0] = '-';
	else if (f[0] || f[1])
		created[0] = f[1] ? '+' : ' ';
	ft_itoa_u((intmax_t)nb, created + sln - len, 1, f[5]);
	ft_fitoa_u(nb, created + sln - w[1] - 4, w[1]);
	ft_exp_u(created + sln - 4, exp, is_upper);
	if (w[0] == size && !f[3] && ft_memrcpy(created + size - sln, created, sln))
		ft_memset(created, f[2] ? '0' : ' ', size - sln);
	else if (w[0] == size && f[3])
		ft_memset(created + sln, ' ', sln);
	return (end_conv_nothing(0, f, created, size));
}
