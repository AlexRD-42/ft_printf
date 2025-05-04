/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/04 11:39:20 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// This could hold the STR or Number with va_args already!
// If invalid, set to pointer and read the invalid byte as a number
// fields: uint64_t number, char *str, size_t len

static t_flags	ft_setflags(const char *str, const char type, const char *end)
{
	t_flags		flags;
	const char	*digit = ft_strfind(str, "123456789", 1);
	const char	*dot = ft_strchr(str, '.');
	const char	zpad = !!ft_strchr(str, '0') && (ft_strchr(str, '0') < digit);
	size_t		lut[256];

	ft_memset(lut, 0, sizeof(lut));
	while (str < end)
		lut[(uint8_t)(*str++)] += 1;
	flags.type = type;
	flags.numeric = ft_strchr("pdiuxX", type) != NULL;
	flags.base_index = (type == 'x' || type == 'p') + ((type == 'X') << 1);
	flags.precision = 0;
	flags.width = 0;
	flags.dot = lut['.'];
	flags.sign = ' ' * (lut[' '] && !lut['+']) + '+' * !!lut['+'];
	flags.prefix = 'x' * ((lut['#'] && type == 'x') || type == 'p');
	flags.prefix += 'X' * (lut['#'] && type == 'X');
	if (dot != NULL && type != 'p')
		flags.precision = ft_atoi(dot + 1);
	if ((digit < dot) || (dot == NULL && digit != NULL))
		flags.width = ft_atoi(digit);
	flags.pad = ' ' + 13 * (!!lut['-']);
	flags.pad += 16 * (!lut[45] && !lut[32] && zpad && flags.numeric && !dot);
	return (flags);
}

static char	*ft_getnum(char *ptr, uint64_t number, t_flags flags)
{
	static const char	*base[3] = {B_DEC, B_HEX_LOW, B_HEX_UP};

	if ((flags.type == 'd' || flags.type == 'i') && (int32_t) number < 0)
	{
		flags.sign = '-';
		number = (uint32_t)(-(int64_t)number);
	}
	ptr = ft_utoa(number, base[flags.base_index], ptr, flags.precision);
	if (flags.sign != 0)
		*(--ptr) = flags.sign;
	if (flags.prefix != 0 && number != 0)
	{
		*(--ptr) = flags.prefix;
		*(--ptr) = '0';
	}
	return (ptr);
}

static char	*ft_getstr(char *buffer, t_flags flags, va_list args)
{
	uint64_t	number;
	char		*str;

	number = 0;
	*(buffer) = '%';
	if (flags.type == 's')
	{
		str = (char *) va_arg(args, char *);
		if (str == NULL)
			return (ft_memcpy(buffer, "(null)", 7));
	}
	else if (flags.type == 'c')
		*buffer = (char)va_arg(args, int);
	else if (flags.type == 'p')
		number = (uintptr_t) va_arg(args, void *);
	else if (flags.numeric > 0)
		number = va_arg(args, unsigned int);
	if (flags.type == 'p' && number == 0)
		return (ft_memcpy(buffer, "(nil)", 6));
	if (flags.type == 's')
		return (str);
	if (flags.type == '%' || flags.type == 'c')
		return (buffer);
	return (ft_getnum(buffer + MAX_WIDTH - 1, number, flags));
}

static int	ft_parse(const char *str, char *ptr, va_list args, const char **addr)
{
	t_flags		flags;
	const char	*ostr = str - 1;
	const char	*end = ft_strfind(str + 1, "-+#. 0123456789", 0);

	ft_memset(ptr, 0, MAX_WIDTH);
	*addr = end + 1;
	flags = ft_setflags(ostr + 1, *end, end);
	if (flags.dot > 1 || ft_strchr("cspdiuxX%", (uint8_t) * end) == NULL)
		return (write(1, ostr, end - ostr + 1));
	ptr = ft_getstr(ptr, flags, args);
	if (flags.type == 'c' || flags.type == '%')
		return (ft_print(ptr, 1, flags));
	else
		return (ft_print(ptr, ft_strlen(ptr), flags));
}

// Could make LUT in this (could also make it on setflags)
// But then you run into the problem of not knowing how to return a failure
// Also the setflags function is already 19 lines
int	ft_printf(const char *str, ...)
{
	int			bytes;
	va_list		args;
	const char	*ostr;
	char		buffer[MAX_WIDTH];

	bytes = 0;
	va_start(args, str);
	while (*str != 0)
	{
		ostr = str;
		while (*str != 0 && *str != '%')
			str++;
		bytes += write (1, ostr, str - ostr);
		if (*str == '%')
			bytes += ft_parse(str, buffer, args, &str);
	}
	va_end(args);
	return (bytes);
}

// #include <limits.h>
// #include <stdio.h>
// // #define test  ("%09d %010d %011d %012d %013d %014d %015d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42)

// #define test ("%d", INT_MIN)
// int main()
// {
// 	ft_printf test;
// 	printf("\n");
// 	printf test;
// }