/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/04 13:06:39 by adeimlin         ###   ########.fr       */
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

	if (flags.type == 'p' && number == 0)
		return (ft_memcpy(ptr, "(nil)", 6));
	if ((flags.type == 'd' || flags.type == 'i') && (int32_t) number < 0)
	{
		flags.sign = '-';
		number = (uint32_t)(-(int64_t)number);
	}
	ptr = ft_utoa(number, base[flags.base_index], ptr + MAX_WIDTH - 1, flags.precision);
	if (flags.sign != 0)
		*(--ptr) = flags.sign;
	if (flags.prefix != 0 && number != 0)
	{
		*(--ptr) = flags.prefix;
		*(--ptr) = '0';
	}
	return (ptr);
}

static int	ft_parse(const char *str, const char *end, va_list args)
{
	char		buffer[MAX_WIDTH];
	char		*ptr;
	t_flags		flags;

	flags = ft_setflags(str, *end, end);
	if (flags.dot > 1 || ft_strchr("cspdiuxX%", *(uint8_t *)end) == NULL)
		return (write(1, str, end - str));
	ft_memset(buffer, 0, sizeof(buffer));
	ptr = buffer;
	if (flags.type == 's')
	{
		ptr = (char *) va_arg(args, char *);
		if (ptr == NULL)
			ptr = ft_memcpy(buffer, "(null)", 7);
	}
	else if (flags.type == 'c')
		*ptr = (char) va_arg(args, int);
	else if (flags.type == '%')
		*ptr = '%';
	else if (flags.type == 'p')
		ptr = ft_getnum(buffer, (uintptr_t) va_arg(args, void *), flags);
	else
		ptr = ft_getnum(buffer, va_arg(args, unsigned int), flags);
	if (flags.type == 'c' || flags.type == '%')
		return (ft_print(ptr, 1, flags));
	else
		return (ft_print(ptr, ft_strlen(ptr), flags));
}

static int	ft_writef(char *str, size_t len, t_flags flags)
{
	int		bytes;
	size_t	pad_len;

	bytes = 0;
	pad_len = 0;
	if (flags.dot != 0 && len > flags.precision && !flags.numeric)
		len = flags.precision;
	if (len < flags.width)
		pad_len = flags.width - len;
	if (flags.pad == '0' && (*str == 32 || *str == 45 || *str == 43) && len--)
		bytes += write(1, str++, 1);
	if (flags.pad == '-')
	{
		bytes += write(1, str, len);
		bytes += ft_putnchar(' ', pad_len);
	}
	else
	{
		bytes += ft_putnchar(flags.pad, pad_len);
		bytes += write(1, str, len);
	}
	return (bytes);
}

int	ft_printf(const char *str, ...)
{
	int			bytes;
	va_list		args;
	const char	*ostr;

	bytes = 0;
	va_start(args, str);
	while (*str != 0)
	{
		ostr = str;
		while (*str != 0 && *str != '%')
			str++;
		bytes += write (1, ostr, str - ostr);
		if (*str == '%')
		{
			ostr = str;
			str = ft_strfind(str + 1, "-+#. 0123456789", 0);
			bytes += ft_parse(ostr, str++, args);
		}
	}
	va_end(args);
	return (bytes);
}

// #include <limits.h>
// #include <stdio.h>

// #define test ("%5..5d", INT_MIN, 42)
// int main()
// {
// 	ft_printf test;
// 	printf("\n");
// 	printf test;
// }