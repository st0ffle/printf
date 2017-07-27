// static int	octets_to_print(char *str)
// {
// 	t_byte	octet;

// 	octet = (t_byte)*str;
// 	if ((octet & 128) == 0)
// 		return (1);
// 	if ((octet & 224) == 192)
// 		return (2);
// 	if ((octet & 240) == 224)
// 		return (3);
// 	if ((octet & 248) == 240)
// 		return (4);
// 	return (0);
// }

// static void	apply_precision(char **data, int *size, t_format frmt)
// {
// 	int	to_print;
// 	int	i;

// 	if ((frmt.specifier == 'c' || frmt.specifier == 'C'))
// 		return ;
// 	if (frmt.specifier == 'S')
// 	{
// 		i = 0;
// 		to_print = 0;
// 		while (to_print + i <= frmt.precision)
// 		{
// 			to_print += i;
// 			i = octets_to_print(*data + to_print);
// 		}
// 		(*data)[to_print] = '\0';
// 		*size = to_print;
// 	}
// 	else
// 	{
// 		(*data)[frmt.precision] = '\0';
// 		*size = frmt.precision;
// 	}
// }

// static void	apply_width(char **data, int *size, t_format frmt)
// {
// 	int		width;
// 	char	*to_add;
// 	char	*tmp;

// 	width = frmt.width;
// 	if (width > *size)
// 	{
// 		tmp = *data;
// 		if (frmt.flags.zero == 0 || frmt.flags.dash)
// 			*data = ft_strcnew(width, ' ');
// 		else
// 			*data = ft_strcnew(width, '0');
// 		if (frmt.flags.dash == 0)
// 			ft_strncpy(*data + width - *size, tmp, *size);
// 		else
// 			ft_strncpy(*data, tmp, *size);
// 		*size = width;
// 		free(tmp);
// 	}
// }

// void		ftpf_process_characters(char **data, int *size,
// 									t_format frmt)
// {
// 	if (frmt.precision > -1 && frmt.precision < *size)
// 		apply_precision(data, size, frmt);
// 	if (frmt.width > 0)
// 		apply_width(data, size, frmt);
// }