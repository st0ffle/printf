/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 05:24:59 by mgonon            #+#    #+#             */
/*   Updated: 2017/07/28 06:49:33 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_strupper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}

static void	apply_zero_cases(char **res_str, int *tmp_len, t_format *frmt)
{
	int	i;

	i = 0;
	while ((*res_str)[i])
	{
		if (ft_isdigit((*res_str)[i]) == 0)
			return ;
		i++;
	}
	if (frmt->precision == 0)
	{
		**res_str = '\0';
		*tmp_len = 0;
	}
	if (frmt->specifier == 'x' || frmt->specifier == 'X')
		frmt->flags.sharp = 0;
}

static void	apply_sharp_flag(char **res_str, int *tmp_len, char id)
{
	char *tmp;

	tmp = *res_str;
	if (id == 'o' || id == 'O')
	{
		if (**res_str == '0')
			return ;
		*res_str = ft_strjoin("0", *res_str);
		*tmp_len += 1;
		free(tmp);
	}
	else if (id == 'x' || id == 'X' || id == 'p')
	{
		*res_str = ft_strjoin("0x", *res_str);
		*tmp_len += 2;
		free(tmp);
	}
}

static void	apply_precision(char **res_str, int *tmp_len, t_format frmt)
{
	int		precision;
	char	*to_add;
	char	*tmp;

	precision = frmt.precision;
	tmp = *res_str;
	to_add = ft_strnew_c(precision - *tmp_len, '0');
	*res_str = ft_strjoin(to_add, *res_str);
	*tmp_len = precision;
	free(tmp);
	free(to_add);
}

static void	apply_width_nominus(char **res_str, int *tmp_len, t_format frmt)
{
	int		width;
	char	*to_add;
	char	*tmp;

	width = frmt.width;
	tmp = *res_str;
	if (frmt.flags.zero == 0 || frmt.precision > 0)
		to_add = ft_strnew_c(width - *tmp_len, ' ');
	else if (frmt.flags.sharp &&
			(frmt.specifier == 'x' || frmt.specifier == 'X' ||
			frmt.specifier == 'p'))
	{
		(*res_str) += 2;
		to_add = ft_strnew_c(width - *tmp_len + 2, '0');
		to_add[0] = '0';
		to_add[1] = 'x';
	}
	else
		to_add = ft_strnew_c(width - *tmp_len, '0');
	*res_str = ft_strjoin(to_add, *res_str);
	*tmp_len = width;
	free(tmp);
	free(to_add);
}

void		fill_unsigned(char **res_str, int *tmp_len, t_format frmt)
{
	if (frmt.precision > *tmp_len)
		apply_precision(res_str, tmp_len, frmt);
	if (ft_atoi(*res_str) == 0)
		apply_zero_cases(res_str, tmp_len, &frmt);
	if (frmt.flags.sharp)
		apply_sharp_flag(res_str, tmp_len, frmt.specifier);
	if (frmt.width > *tmp_len && frmt.flags.minus == 0)
		apply_width_nominus(res_str, tmp_len, frmt);
	if (frmt.width > *tmp_len && frmt.flags.minus == 1)
		apply_width_minus(res_str, tmp_len, frmt.width);
	if (frmt.specifier == 'X')
		ft_strupper(*res_str);
}