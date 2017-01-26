/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 04:11:46 by mgonon            #+#    #+#             */
/*   Updated: 2017/01/16 04:20:06 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_flag(char c)
{
	return (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+');
}

int	is_length(char c)
{
	return (c == 'l' || c == 'h' || c == 'j' || c == 'z');
}

int	is_specifier(char c)
{
	return (c == 'p' || c == 'd' ||
			c == 'i' || c == 'o' ||
			c == 'O' || c == 'x' ||
			c == 'X' || c == 'D' ||
			c == 'u' || c == 'U' ||
			c == 'C' || c == 'c' ||
			c == 's' || c == 'S');
}