/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 03:31:27 by mgonon            #+#    #+#             */
/*   Updated: 2017/08/18 14:27:26 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*get_arg_c(va_list args, int *tmp_len)
{
	char	arg;
	char	*res_str;

	arg = (char)va_arg(args, int);
	res_str = ft_strnew_c(1, arg);
	*tmp_len = 1;
	return (res_str);
}

static char	*get_arg_s(va_list args, int *tmp_len)
{
	char	*arg;
	char	*res_str;

	arg = (char*)va_arg(args, char*);
	if (arg != NULL)
		res_str = ft_strdup(arg);
	else
		res_str = ft_strdup("(null)");
	*tmp_len = ft_strlen(res_str);
	return (res_str);
}

static char	*get_arg_lc(va_list args, int *tmp_len)
{
	wint_t	arg;
	char	*res_str;

	arg = (wint_t)va_arg(args, wint_t);
	if (!(res_str = get_unicode_char(arg)))
		return (NULL);
	if ((*tmp_len = ft_strlen(res_str)) == 0)
		*tmp_len = 1;
	return (res_str);
}

static char	*get_arg_ls(va_list args, int *tmp_len)
{
	wchar_t	*arg;
	char	*res_str;

	arg = (wchar_t*)va_arg(args, wchar_t*);
	if (arg != NULL)
	{
		if (!(res_str = get_unicode_str(arg)))
			return (NULL);
	}
	else
		res_str = get_unicode_str(L"(null)");
	*tmp_len = ft_strlen(res_str);
	return (res_str);
}

char		*get_char_arg(va_list args, t_format frmt, int *tmp_len)
{
	char	*res_str;

	if (frmt.specifier == 'C' || (frmt.specifier == 'c' && frmt.length.l))
		res_str = get_arg_lc(args, tmp_len);
	else if (frmt.specifier == 'S' || (frmt.specifier == 's' && frmt.length.l))
		res_str = get_arg_ls(args, tmp_len);
	else if (frmt.specifier == 'c')
		res_str = get_arg_c(args, tmp_len);
	else if (frmt.specifier == 's')
		res_str = get_arg_s(args, tmp_len);
	return (res_str);
}
