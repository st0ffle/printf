/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 12:47:48 by mgonon            #+#    #+#             */
/*   Updated: 2017/01/26 17:31:33 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

/*static const t_conv g_conv[] = {
	{ "bdiouxX", int_arg },
	{ "DOU", dou_arg },
	{ "Cc", c_arg },
	{ "s", s_arg },
	{ "S", ws_arg },
	{ "p", p_arg },
	{ "%", pct_arg }
};*/

static const t_conv g_conv[] = {
	{ "d", handle_d }
	//{ "%", toto_limit}
};

void	ft_putnstr(char *str, int end)
{
	int	i;

	i = 0;
	while (i < end)
		ft_putchar(str[i++]);
}

// int	ft_printf(const char *format, ...)
// {
// 	int		i;
// 	int		len;
// 	va_list	args;
	
// 	va_start(args, format);


// 	i = 0;
// 	while (format[i])
// 	{
// 		if (format[i] == '%')
// 		{
// 			len = 0;
// 			while (!is_type(format[i]) && format[i])
// 			{
// 				i++;
// 				len++;
// 			}
// 			i++;
// 			printf("%d", va_arg(args, int));
// 			//printf("i = %d, len = %d, char = %c\n", i, len, format[i]);
// 		}
// 		write(1, &format[i], 1);
// 		i++;
// 	}	
// 	va_end(args);
// 	return (0);
// }

void	init_format(t_format *frmt)
{
	frmt->flags.minus = 0;
	frmt->flags.plus = 0;
	frmt->flags.space = 0;
	frmt->flags.sharp = 0;
	frmt->flags.zero = 0;
	frmt->width = -42;
	frmt->precision = -42;
	frmt->length.h = 0;
	frmt->length.l = 0;
	frmt->length.j = 0;
	frmt->length.z = 0;
	frmt->specifier = 0;
}

void	get_format(char const **format, t_format *frmt, va_list args)
{
	//printf("**format = %c\n", **format);
	while (is_flag(**format) || is_length(**format) ||
			ft_isdigit(**format) || **format == '*' ||
			**format == '.')
	{
		// printf("\n**format = %c\n", **format);
		if (is_flag(**format))
			get_flags(format, frmt);
		else if (ft_isdigit(**format) || **format == '*')
			get_width(format, frmt, args);
		else if (**format == '.')
			get_precision(format, frmt, args);
		else if (is_length(**format))
			get_length(format, frmt);
		// printf("\n**format = %c\n", **format);
		//(*format)++;
		// printf("\n**format = %c\n", **format);
	}
	if (is_specifier(**format))
	{
		frmt->specifier = **format;
		(*format)++;
	}
	else
		printf("**format = %c, why no specifier ?!\n", **format);
}

char	*get_result_str(const char **format, va_list args, t_format *frmt)
{
	char	*buf;
	int		i;

	i = 0;
	buf = ft_memalloc(10000);
	if(!(buf = (char *)malloc(sizeof(*buf) * 10000)))
		return (NULL);
	//ft_bzero(buf, 10000);
	init_format(frmt);
	get_format(format, frmt, args);
	//printf("width = %d\n z = %d\n specifier = %c\n", frmt->width, frmt->length.z, frmt->specifier);
	while (i < 1)
	{
		if (ft_strchr(g_conv[i].specifier, frmt->specifier))
			g_conv[i].handle(va_arg(args, int), buf, frmt);
		i++;
	}
	//write(1, buf, ft_strlen(buf));
	//printf("%s\n", buf);
	return (NULL);
	//get_format(frmt)
}

// size_t	analyze(va_list args, const char *format)
// {
// 	size_t		len;
// 	t_format	frmt;
// 	char		*ptr;
// 	char		*start;

// 	len = 0;
// 	ptr = (char *)format;
// 	start = (char *)format;
// 	while (*ptr != '\0')
// 	{
// 		if (*ptr == '%')
// 		{
// 			ft_putnstr(start, ptr - start);
// 			ptr++;
// 			get_result_str(ptr, args, &frmt);
// 			//len +=
// 			start = ptr;
// 			ptr++;
// 		}
// 		else if (*ptr != '\0')
// 		{
// 			len++;
// 			ptr++;
// 		}
// 	}
// 	ft_putnstr(start, ptr - start);
// 	return (len);
// }

// size_t	analyze(va_list args, const char *format)
// {
// 	size_t		len;
// 	t_format	frmt;
// 	char		*start;

// 	len = 0;
// 	start = (char *)format;
// 	while (*format != '\0')
// 	{
// 		if (*format == '%')
// 		{
// 			ft_putnstr(start, format - start);
// 			format++;
// 			get_result_str(&format, args, &frmt);
// 			//len +=
// 			start = (char *)format;
// 			format++;
// 		}
// 		else if (*format != '\0')
// 		{
// 			len++;
// 			format++;
// 		}
// 	}
// 	ft_putnstr(start, format - start);
// 	return (len);
// }

int		ft_printf(const char *format, ...)
{

	size_t		len;
	char		*start;
	t_format	frmt;
	va_list		args;

	len = 0;
	va_start(args, format);
	start = (char *)format;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			write(1, start, format - start);
			format++;
			get_result_str(&format, args, &frmt);
			//len +=
			start = (char *)format;
			format++;
		}
		else if (*format != '\0')
		{
			len++;
			format++;
		}
	}
	write(1, start, format - start);
	va_end(args);
	return (len);
}


int	main()
{
	// ft_printf("ft_printf .10d, 12345 = %.10d\n", 12345);
	// printf("printf 10.10d, 12345 = %.10d\n", 12345);
	//ft_printf("toto %.10d eogiwhod %32d", 12, 24);

	ft_printf("1chiffre 1 %+-10.3d chiffre 2 %+-10.3d\n", 42, -42);
  printf("1chiffre 1 %+-10.3d chiffre 2 %+-10.3d\n", 42, -42);

  ft_printf("2chiffre 1 %-10.3d chiffre 2 %-10.3d\n", 42, -42);
  printf("2chiffre 1 %-10.3d chiffre 2 %-10.3d\n", 42, -42);

 	// ft_printf("2chiffre 1 % d chiffre 2 % d\n", 42, -42);
  // printf("2chiffre 1 % d chiffre 2 % d\n", 42, -42);

 	// ft_printf("3chiffre 1 %12d chiffre 2 %12d\n", 42, -42);
  // printf("3chiffre 1 %12d chiffre 2 %12d\n", 42, -42);

 	// ft_printf("4chiffre 1 %-012d chiffre 2 %-012d\n", 42, -42);
  // printf("4chiffre 1 %-012d chiffre 2 %-012d\n", 42, -42);

 	// ft_printf("5chiffre 1 %010d chiffre 2 %010d\n", 42, -42);
  // printf("5chiffre 1 %010d chiffre 2 %010d\n", 42, -42);

 	// ft_printf("6chiffre 1 %012d chiffre 2 %012d\n", 42, -42);
  // printf("6chiffre 1 %012d chiffre 2 %012d\n", 42, -42);

 	// ft_printf("7chiffre 1 %-012d chiffre 2 %012d\n", 42, -42);
  // printf("7chiffre 1 %-012d chiffre 2 %012d\n", 42, -42);

 	// ft_printf("8chiffre 1 %*d chiffre 2 %*d\n", 42, 6, 6, 6);
  // printf("8chiffre 1 %*d chiffre 2 %*d\n", 42, 6, 6, 6);

 	// ft_printf("9chiffre 1 %+d chiffre 2 %+d\n", 42, 6, -42, 6);
  // printf("9chiffre 1 %+d chiffre 2 %+d\n", 42, 6, -42, 6);

 	// ft_printf("10chiffre 1 %+12d chiffre 2 %+12d\n", 42, 6, -42, 6);
  // printf("10chiffre 1 %+12d chiffre 2 %+12d\n", 42, 6, -42, 6);

 	// ft_printf("11chiffre 1 %*12d chiffre 2 %*12d\n", 42, -6, 42, 6);
  // printf("11chiffre 1 %*12d chiffre 2 %*12d\n", 42, -6, 42, 6);
  
 	// ft_printf("12chiffre 1 %-+5d chiffre 2 %-+5d\n", 42, -42);
  // printf("12chiffre 1 %-+5d chiffre 2 %-+5d\n", 42, -42);  

 	// ft_printf("13chiffre 1 %-+05d chiffre 2 %-+05d\n", 42, -42);
  // printf("13chiffre 1 %-+05d chiffre 2 %-+05d\n", 42, -42);

 	// ft_printf("14chiffre 1 %+-5d chiffre 2 %+-5d\n", 42, -42);
  // printf("14chiffre 1 %+-5d chiffre 2 %+-5d\n", 42, -42);

 	// ft_printf("15chiffre 1 %.d chiffre 2 %.d\n", 42, -42);
  // printf("15chiffre 1 %.d chiffre 2 %.d\n", 42, -42);

 	// ft_printf("16chiffre 1 %.6d chiffre 2 %.6d\n\n\n", 42, -42);
  // printf("16chiffre 1 %.6d chiffre 2 %.6d\n", 42, -42);
	return (0);
}