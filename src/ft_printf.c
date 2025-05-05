/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/05 12:47:38 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

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
	flags.precision = 0;
	flags.width = 0;
	flags.dot = lut['.'];
	flags.sign = ' ' * (lut[' '] && !lut['+']) + '+' * !!lut['+'];
	flags.prefix = 'x' * ((lut['#'] && type == 'x') || type == 'p');
	flags.prefix += 'X' * (lut['#'] && type == 'X');
	if (dot != NULL && type != 'p')
		flags.precision = ft_atoi_f(dot + 1, end);
	if ((digit < dot) || (dot == NULL && digit != NULL))
		flags.width = ft_atoi_f(digit, end);
	flags.pad = ' ' + 13 * (!!lut['-']);
	flags.pad += 16 * (!lut[45] && !lut[32] && zpad && flags.numeric && !dot);
	return (flags);
}

static char	*ft_getstr(char *ptr, uintptr_t number, t_flags flags)
{
	if (flags.type == 's' && number == 0)
		return (ft_memcpy(ptr, "(null)", 7));
	if (flags.type == 'p' && number == 0)
		return (ft_memcpy(ptr, "(nil)", 6));
	*ptr = (char) number;
	if (flags.type == 's')
		return ((char *) number);
	if (flags.type == 'c' || flags.type == 's')
		return (ptr);
	ptr = ft_itoa_f(number, flags.type, ptr + MAX_WIDTH - 1, flags.precision);
	if (flags.sign != 0 && *ptr != '-')
		*(--ptr) = flags.sign;
	if (flags.prefix != 0 && number != 0)
	{
		*(--ptr) = flags.prefix;
		*(--ptr) = '0';
	}
	return (ptr);
}

static int	ft_writef(char *str, size_t len, t_flags flags)
{
	int		bytes;
	size_t	pad_len;

	bytes = 0;
	pad_len = 0;
	if (len < flags.width)
		pad_len = flags.width - len;
	if (flags.pad == '-')
	{
		bytes += write(1, str, len);
		bytes += ft_putnchar(' ', pad_len);
	}
	else
	{
		if (flags.pad == '0' && (flags.sign != 0 || *str == '-') && len--)
			bytes += write(1, str++, 1);
		bytes += ft_putnchar(flags.pad, pad_len);
		bytes += write(1, str, len);
	}
	return (bytes);
}

static int	ft_parse(const char *str, const char *end, va_list args)
{
	uintptr_t	va_var;
	char		buffer[MAX_WIDTH];
	char		*ptr;
	t_flags		flags;
	size_t		length;

	flags = ft_setflags(str, *end, end);
	if (flags.dot > 1 || ft_strchr("cspdiuxX", *(uint8_t *)end) == NULL)
		return (write(1, str, end - str));
	ft_memset(buffer, 0, sizeof(buffer));
	if (flags.type == 's' || flags.type == 'p')
		va_var = (uintptr_t) va_arg(args, void *);
	else
		va_var = va_arg(args, unsigned int);
	ptr = ft_getstr(buffer, va_var, flags);
	length = 1;
	if (flags.type != 'c')
		length = ft_strlen(ptr);
	if (flags.type == 's' && flags.dot != 0 && flags.precision < length)
		length = flags.precision;
	if (flags.numeric && flags.dot != 0 && flags.precision < length && !va_var)
		length = flags.precision;
	if (flags.type == 's' && flags.dot != 0 && flags.precision < 6 && !va_var)
		length = 0;
	return (ft_writef(ptr, length, flags));
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
			if (*str == '%')
				bytes += write(1, "%", 1);
			else
				bytes += ft_parse(ostr, str, args);
			str++;
		}
	}
	va_end(args);
	return (bytes);
}

// #include <limits.h>
// #include <stdio.h>

// // .0 precision makes it so 0 doesn't show but != 0 shows
// // precision lower than 7 makes it so null doesn't show at all
// #define test ("%.6s", NULL)
// int main()
// {
// 	ft_printf test;
// 	printf("\n");
// 	printf test;
// }