/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 12:47:48 by mgonon            #+#    #+#             */
/*   Updated: 2017/03/09 09:17:56 by mgonon           ###   ########.fr       */
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
	{ "dioxX", handle_di }
	//{ "%", toto_limit}
};

void	init_format(t_format *frmt)
{
	frmt->flags.minus = 0;
	frmt->flags.plus = 0;
	frmt->flags.space = 0;
	frmt->flags.sharp = 0;
	frmt->flags.zero = 0;
	frmt->width = 0;
	frmt->precision = -1;
	frmt->length.h = 0;
	frmt->length.l = 0;
	frmt->length.j = 0;
	frmt->length.z = 0;
	frmt->specifier = 0;
}

void	get_format(char const **format, t_format *frmt, va_list args)
{
	while (is_flag(**format) || is_length(**format) ||
			ft_isdigit(**format) || **format == '*' ||
			**format == '.')
	{
		if (is_flag(**format))
			get_flags(format, frmt);
		else if (ft_isdigit(**format) || **format == '*')
			get_width(format, frmt, args);
		else if (**format == '.')
			get_precision(format, frmt, args);
		else if (is_length(**format))
			get_length(format, frmt);
	}
	if (is_specifier(**format))
	{
		frmt->specifier = **format;
		(*format)++;
	}
	else
		printf("**format = %c, why no specifier ?!\n", **format);
	if (frmt->precision >= 0 && frmt->flags.zero)
		frmt->flags.zero = 0;
}

uintmax_t	get_arg(t_format frmt, va_list args)
{
	uintmax_t	arg;

	if (is_signed(frmt.specifier))
		arg = get_signed_arg(args, frmt.specifier, frmt.length);
	else if (is_unsigned(frmt.specifier))
		arg = get_unsigned_arg(args, frmt.specifier, frmt.length);
	return (arg);
}

int		get_result_str(const char **format, va_list args, t_format *frmt)
{
	char		*buf;
	uintmax_t	arg;
	int			len;
	int			i;

	i = 0;
	len = 0;
	// buf = ft_memalloc(10000);
	if(!(buf = (char *)malloc(sizeof(*buf) * 10000)))
		return (0);
	ft_bzero(buf, 10000);
	init_format(frmt);
	get_format(format, frmt, args);
	arg = get_arg(*frmt, args);
	//printf("width = %d\n z = %d\n specifier = %c\n", frmt->width, frmt->length.z, frmt->specifier);
	while (i < 1)
	{
		if (ft_strchr(g_conv[i].specifier, frmt->specifier))
			len = g_conv[i].handle(arg, buf, frmt);
		else
			return (len);
		i++;
	}
	//write(1, buf, ft_strlen(buf));
	//printf("%s\n", buf);
	return (len);
	//get_format(frmt)
}

int		ft_printf(const char *format, ...)
{
	int			len;
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
			// printf("\n len main = %d\n", len);
			len += get_result_str(&format, args, &frmt);
			// printf("\n len main2 = %d\n", len);
			//len +=
			start = (char *)format;
			format++;
			len++;
		}
		else if (*format != '\0')
		{
			len++;
			format++;
		}
	}
	write(1, start, format - start);
	// printf("\n len main3 = %d\n", len);
	va_end(args);
	return (len);
}


// int	main()
// {
	// // ft_printf("ft_printf .10d, 12345 = %.10d\n", 12345);
	// // printf("printf 10.10d, 12345 = %.10d\n", 12345);
	// // ft_printf("toto %.10d eogiwhod %32d", 12, 24);


  /* Verification des decimals, %i et %d */

//   ft_printf("%d\n", ft_printf("1chiffre 1 %d chiffre 2 %d\n", 42, -42));
//   printf("%d\n", printf("1chiffre 1 %d chiffre 2 %d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("2chiffre 1 %   d chiffre 2 % d\n", 42, -42));
//   printf("%d\n", printf("2chiffre 1 %   d chiffre 2 % d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("3chiffre 1 %12d chiffre 2 %12d\n", 42, -42));
//   printf("%d\n", printf("3chiffre 1 %12d chiffre 2 %12d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("4chiffre 1 %-12d chiffre 2 %-12d\n", 42, -42));
//   printf("%d\n", printf("4chiffre 1 %-12d chiffre 2 %-12d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("5chiffre 1 %0d chiffre 2 %0d\n", 42, -42));
//   printf("%d\n", printf("5chiffre 1 %0d chiffre 2 %0d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("6chiffre 1 %012d chiffre 2 %012d\n", 42, -42));
//   printf("%d\n", printf("6chiffre 1 %012d chiffre 2 %012d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("7chiffre 1 %-012d chiffre 2 %012d\n", 42, -42));
//   printf("%d\n", printf("7chiffre 1 %-012d chiffre 2 %012d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("8chiffre 1 %*d chiffre 2 %*d\n", 42, 6, 6, 6));
//   printf("%d\n", printf("8chiffre 1 %*d chiffre 2 %*d\n", 42, 6, 6, 6));

//   ft_printf("%d\n", ft_printf("9chiffre 1 %+d chiffre 2 %+d\n", 42, 6, -42, 6));
//   printf("%d\n", printf("9chiffre 1 %+d chiffre 2 %+d\n", 42, 6, -42, 6));

//   ft_printf("%d\n", ft_printf("10chiffre 1 %+12d chiffre 2 %+12d\n", 42, 6, -42, 6));
//   printf("%d\n", printf("10chiffre 1 %+12d chiffre 2 %+12d\n", 42, 6, -42, 6));

//   ft_printf("%d\n", ft_printf("11chiffre 1 %*12d chiffre 2 %*12d\n", 42, -6, 42, 6));
//   printf("%d\n", printf("11chiffre 1 %*12d chiffre 2 %*12d\n", 42, -6, 42, 6));
  
//   ft_printf("%d\n", ft_printf("12chiffre 1 %-+5d chiffre 2 %-+5d\n", 42, -42));
//   printf("%d\n", printf("12chiffre 1 %-+5d chiffre 2 %-+5d\n", 42, -42));  

//   ft_printf("%d\n", ft_printf("13chiffre 1 %-+05d chiffre 2 %-+05d\n", 42, -42));
//   printf("%d\n", printf("13chiffre 1 %-+05d chiffre 2 %-+05d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("14chiffre 1 %+-5d chiffre 2 %+-5d\n", 42, -42));
//   printf("%d\n", printf("14chiffre 1 %+-5d chiffre 2 %+-5d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("15chiffre 1 %.d chiffre 2 %.d\n", 42, -42));
//   printf("%d\n", printf("15chiffre 1 %.d chiffre 2 %.d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("16chiffre 1 %.6d chiffre 2 %.6d\n", 42, -42));
//   printf("%d\n", printf("16chiffre 1 %.6d chiffre 2 %.6d\n", 42, -42));

//   ft_printf("%d\n", ft_printf("16chiffre 1 %.8d chiffre 2 %.8d\n", -442, -42));
//   printf("%d\n", printf("16chiffre 1 %.8d chiffre 2 %.8d\n", -442, -42));

//   	ft_printf("1chiffre 1 %-010.5d chiffre 2 %-010.5d\n", 42, -42);
//   printf("1chiffre 1 %-010.5d chiffre 2 %-010.5d\n", 42, -42);

//   	ft_printf("2chiffre 1 %010.5d chiffre 2 %010.5d\n", 42, -42);
//   printf("2chiffre 1 %010.5d chiffre 2 %010.5d\n", 42, -42);

//  	ft_printf("2chiffre 1 % d chiffre 2 % d\n", 42, -42);
//   printf("2chiffre 1 % d chiffre 2 % d\n", 42, -42);

//  	ft_printf("3chiffre 1 %12d chiffre 2 %12d\n", 42, -42);
//   printf("3chiffre 1 %12d chiffre 2 %12d\n", 42, -42);

//  	ft_printf("4chiffre 1 %-012d chiffre 2 %-012d\n", 42, -42);
//   printf("4chiffre 1 %-012d chiffre 2 %-012d\n", 42, -42);

//  	ft_printf("5chiffre 1 %010d chiffre 2 %010d\n", 42, -42);
//   printf("5chiffre 1 %010d chiffre 2 %010d\n", 42, -42);

//  	ft_printf("6chiffre 1 %012d chiffre 2 %012d\n", 42, -42);
//   printf("6chiffre 1 %012d chiffre 2 %012d\n", 42, -42);

//  	ft_printf("7chiffre 1 %-012d chiffre 2 %012d\n", 42, -42);
//   printf("7chiffre 1 %-012d chiffre 2 %012d\n", 42, -42);

//  	ft_printf("8chiffre 1 %*d chiffre 2 %*d\n", 42, 6, 6, 6);
//   printf("8chiffre 1 %*d chiffre 2 %*d\n", 42, 6, 6, 6);

//  	ft_printf("9chiffre 1 %+d chiffre 2 %+d\n", 42, 6, -42, 6);
//   printf("9chiffre 1 %+d chiffre 2 %+d\n", 42, 6, -42, 6);

//  	ft_printf("10chiffre 1 %+12d chiffre 2 %+12d\n", 42, 6, -42, 6);
//   printf("10chiffre 1 %+12d chiffre 2 %+12d\n", 42, 6, -42, 6);

//  	ft_printf("11chiffre 1 %*12d chiffre 2 %*12d\n", 42, -6, 42, 6);
//   printf("11chiffre 1 %*12d chiffre 2 %*12d\n", 42, -6, 42, 6);
  
//  	ft_printf("12chiffre 1 %-+5d chiffre 2 %-+5d\n", 42, -42);
//   printf("12chiffre 1 %-+5d chiffre 2 %-+5d\n", 42, -42);  

//  	ft_printf("13chiffre 1 %-+05d chiffre 2 %-+05d\n", 42, -42);
//   printf("13chiffre 1 %-+05d chiffre 2 %-+05d\n", 42, -42);

//  	ft_printf("14chiffre 1 %+-5d chiffre 2 %+-5d\n", 42, -42);
//   printf("14chiffre 1 %+-5d chiffre 2 %+-5d\n", 42, -42);

//  	ft_printf("15chiffre 1 %.d chiffre 2 %.d\n", 42, -42);
//   printf("15chiffre 1 %.d chiffre 2 %.d\n", 42, -42);

//  	ft_printf("16chiffre 1 %.6d chiffre 2 %.6d\n\n\n", 42, -42);
//   printf("16chiffre 1 %.6d chiffre 2 %.6d\n", 42, -42);




















	
// 	int	ret;

// 	// test for %d 0; //
// 	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n          test for %%d 0;\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

// 	printf("------------------------------------\n");
// 	ret = printf("{%d}\n", 0);
// 	printf("%35s%d\n", "printf('%d', 0) ret : ", ret);
// 	ret = ft_printf("{%d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%+d}\n", 0);
// 	printf("%35s%d\n", "printf('%+d', 0) ret : ", ret);
// 	ret = ft_printf("{%+d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%+d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%.d}\n", 0);
// 	printf("%35s%d\n", "printf('%.d', 0) ret : ", ret);
// 	ret = ft_printf("{%.d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%.d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%.5d}\n", 0);
// 	printf("%35s%d\n", "printf('%.5d', 0) ret : ", ret);
// 	ret = ft_printf("{%.5d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%.5d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%.0d}\n", 0);
// 	printf("%35s%d\n", "printf('%.0d', 0) ret : ", ret);
// 	ret = ft_printf("{%.0d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%.0d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%5.d}\n", 0);
// 	printf("%35s%d\n", "printf('%5.d', 0) ret : ", ret);
// 	ret = ft_printf("{%5.d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%5.d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%5.5d}\n", 0);
// 	printf("%35s%d\n", "printf('%5.5d', 0) ret : ", ret);
// 	ret = ft_printf("{%5.5d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%5.5d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%3.5d}\n", 0);
// 	printf("%35s%d\n", "printf('%3.5d', 0) ret : ", ret);
// 	ret = ft_printf("{%3.5d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%3.5d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%5.3d}\n", 0);
// 	printf("%35s%d\n", "printf('%5.3d', 0) ret : ", ret);
// 	ret = ft_printf("{%5.3d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%5.3d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%+010.d}\n", 0);
// 	printf("%35s%d\n", "printf('%+010.d', 0) ret : ", ret);
// 	ret = ft_printf("{%+010.d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%+010.d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%+010.5d}\n", 0);
// 	printf("%35s%d\n", "printf('% 010.5d', 0) ret : ", ret);
// 	ret = ft_printf("{%+010.5d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('% 010.5d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{% .d}\n", 0);
// 	printf("%35s%d\n", "printf('% .d', 0) ret : ", ret);
// 	ret = ft_printf("{% .d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('% .d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%+.d}\n", 0);
// 	printf("%35s%d\n", "printf('%+.d', 0) ret : ", ret);
// 	ret = ft_printf("{%+.d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%+.d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%3.2d}\n", 0);
// 	printf("%35s%d\n", "printf('%3.2d', 0) ret : ", ret);
// 	ret = ft_printf("{%3.2d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%3.2d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%-3.2d}\n", 0);
// 	printf("%35s%d\n", "printf('%-3.2d', 0) ret : ", ret);
// 	ret = ft_printf("{%-3.2d}\n", 0);
// 	printf("%35s%d\n", "ft_printf('%-3.2d', 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	// test for %d 1; //
// 	ret = printf("{%+010.d}\n", 1);
// 	printf("%35s%d\n", "printf('%+010.d', 1) ret : ", ret);
// 	ret = ft_printf("{%+010.d}\n", 1);
// 	printf("%35s%d\n", "ft_printf('%+010.d', 1) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%+010.0d}\n", 1);
// 	printf("%35s%d\n", "printf('%+010.0d', 1) ret : ", ret);
// 	ret = ft_printf("{%+010.0d}\n", 1);
// 	printf("%35s%d\n", "ft_printf('%+010.0d', 1) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%+10d}\n", 1);
// 	printf("%35s%d\n", "printf('%+10d', 1) ret : ", ret);
// 	ret = ft_printf("{%+10d}\n", 1);
// 	printf("%35s%d\n", "ft_printf('%+10d', 1) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%+010.5d}\n", 1);
// 	printf("%35s%d\n", "printf('%+010.5d', 1) ret : ", ret);
// 	ret = ft_printf("{%+010.5d}\n", 1);
// 	printf("%35s%d\n", "ft_printf('%+010.5d', 1) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%d}\n", -1);
// 	printf("%35s%d\n", "printf('%d', -1) ret : ", ret);
// 	ret = ft_printf("{%d}\n", -1);
// 	printf("%35s%d\n", "ft_printf('%d', -1) ret : ", ret);
// 	printf("------------------------------------\n");

// 	// test for %d 42; //
// 	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n          test for %%d 42;\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

// 	printf("------------------------------------\n");
// 	ret = printf("{%5d}\n", 42);
// 	printf("%35s%d\n", "printf('%5d', 42) ret : ", ret);
// 	ret = ft_printf("{%5d}\n", 42);
// 	printf("%35s%d\n", "ft_printf('%5d', 42) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%05d}\n", 42);
// 	printf("%35s%d\n", "printf('%05d', 42) ret : ", ret);
// 	ret = ft_printf("{%05d}\n", 42);
// 	printf("%35s%d\n", "ft_printf('%05d', 42) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%0+5d}\n", 42);
// 	printf("%35s%d\n", "printf('%0+5d', 42) ret : ", ret);
// 	ret = ft_printf("{%0+5d}\n", 42);
// 	printf("%35s%d\n", "ft_printf('%0+5d', 42) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%5d}\n", -42);
// 	printf("%35s%d\n", "printf('%5d', -42) ret : ", ret);
// 	ret = ft_printf("{%5d}\n", -42);
// 	printf("%35s%d\n", "ft_printf('%5d', -42) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%05d}\n", -42);
// 	printf("%35s%d\n", "printf('%05d', -42) ret : ", ret);
// 	ret = ft_printf("{%05d}\n", -42);
// 	printf("%35s%d\n", "ft_printf('%05d', -42) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%-05d}\n", -42);
// 	printf("%35s%d\n", "printf('%-05d', -42) ret : ", ret);
// 	ret = ft_printf("{%-05d}\n", -42);
// 	printf("%35s%d\n", "ft_printf('%-05d', -42) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%-05d}\n", 42);
// 	printf("%35s%d\n", "printf('%-05d', 42) ret : ", ret);
// 	ret = ft_printf("{%-05d}\n", 42);
// 	printf("%35s%d\n", "ft_printf('%-05d', 42) ret : ", ret);
// 	printf("------------------------------------\n");

// 	// test for %*d ; //
// 	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n          test for %%*d ;\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

// 	printf("------------------------------------\n");
// 	ret = printf("{%*d}\n", -5, 5);	
// 	printf("%35s%d\n", "printf('%*d', -5, 5) ret : ", ret);
// 	ret = ft_printf("{%*d}\n", -5, 5);
// 	printf("%35s%d\n", "ft_printf('%*d', -5, 5) ret : ", ret);
// 	printf("------------------------------------\n");

// 	ret = printf("{%*d}\n", 0, 0);
// 	printf("%35s%d\n", "printf('%*d', 0, 0) ret : ", ret);
// 	ret = ft_printf("{%*d}\n", 0, 0);
// 	printf("%35s%d\n", "ft_printf('%*d', 0, 0) ret : ", ret);
// 	printf("------------------------------------\n");

// 	printf("%d\n", printf("%10.5d\n", 42));
// 	ft_printf("%d\n", ft_printf("%10.5d\n", 42));

// 	ft_printf("%d\n", ft_printf("%.10d\n", 4242));
// 	ft_printf("%d\n", printf("%.10d\n", 4242));
// 	printf("%d\n", printf("%.10d\n", 4242));
// 	printf("%d\n", ft_printf("%.10d\n", 4242));

// 	return (0);
// }
