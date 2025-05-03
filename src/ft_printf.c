/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/03 09:23:59 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// This could hold the STR or Number with va_args already!
// If invalid, set to pointer and read the invalid byte as a number
// fields: uint64_t number, char *str, size_t len
static t_flags	ft_setflags(const char *str, const char type, size_t lut[256])
{
	t_flags		flags;
	const char	*digit = ft_strfind(str, "123456789", 1);
	const char	*dot = ft_strchr(str, '.');
	const char	zpad = !!ft_strchr(str, '0') && (ft_strchr(str, '0') < digit);

	flags.type = type;
	flags.numeric = ft_strchr("pdiuxX", type) != NULL;
	// flags.numeric = (type == 'd' || type == 'i') + ((type == 'u') << 1) + ((type == 'x' || type == 'p') << 2) + ((type == 'X') << 3);
	flags.precision = 0;
	flags.width = 0;
	flags.sign = ' ' * (lut[' '] && !lut['+']) + '+' * !!lut['+'];
	flags.prefix = 'x' * ((lut['#'] && type == 'x') || type == 'p');
	flags.prefix += 'X' * (lut['#'] && type == 'X');
	if (dot != NULL && type != 'p')
		flags.precision = ft_atoi(dot + 1);
	if ((digit < dot) || (dot == NULL && digit != NULL))
		flags.width = ft_atoi(digit);
	flags.pad = ' ' + 13 * (!!lut['-']);
	flags.pad += 16 * (!lut['-'] && !lut[' '] && zpad && flags.numeric && !dot);
	return (flags);
}

// To do: index this disaster with a lut for the bases
static char	*ft_getnum(char *ptr, uint64_t number, t_flags flags)
{
	if (flags.type == 'd' || flags.type == 'i')
		ptr = ft_itoa((int)number, B_DEC, ptr, flags.precision);
	else if (flags.type == 'u')
		ptr = ft_utoa(number, B_DEC, ptr, flags.precision);
	else if (flags.type == 'x')
		ptr = ft_utoa(number, B_HEX_LOW, ptr, flags.precision);
	else if (flags.type == 'X')
		ptr = ft_utoa(number, B_HEX_UP, ptr, flags.precision);
	else if (flags.type == 'p')
		ptr = ft_utoa(number, B_HEX_LOW, ptr, flags.precision);
	if (flags.sign != 0 && *ptr != '-')
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
		str = (char*)va_arg(args, char*);
		if (str == NULL)
			return (ft_memcpy(buffer, "(null)", 7));
	}
	else if (flags.type == 'c')
		*buffer = (char)va_arg(args, int);
	else if (flags.type == 'p')
		number = (uintptr_t) va_arg(args, void *);
	else
		number = va_arg(args, unsigned int);
	if (flags.type == 'p' && number == 0)
		return (ft_memcpy(buffer, "(nil)", 6));
	if (flags.type == 's')
		return (str);
	if (flags.type == '%' || flags.type == 'c')
		return (buffer);
	return (ft_getnum(buffer + MAX_WIDTH - 1, number, flags));
}

int	ft_parse_params(const char *str, char *ptr, va_list args)
{
	t_flags		flags;
	size_t		ltable[256];
	const char	*ostr = str - 1;
	const char	*end = ft_strfind(str + 1, "-+#. 0123456789", 0);
	// size_t		len;

	ft_memset(ltable, 0, sizeof(ltable));
	ft_memset(ptr, 0, MAX_WIDTH);
	while (str < end)
		ltable[(uint8_t)(*str++)] += 1;
	if (ltable['.'] > 1 || ft_strchr("cspdiuxX%", (uint8_t)*end) == NULL)
		return (write(1, ostr, end - ostr + 1));
	flags = ft_setflags(ostr + 1, *end, ltable);
	ptr = ft_getstr(ptr, flags, args);
	if (flags.type == 'c' || flags.type == '%')
		return (ft_print(ptr, 1, flags));
	else
		return (ft_print(ptr, ft_strlen(ptr), flags));
}

int	ft_print(char *str, size_t len, t_flags flags)
{
	int		bytes;
	ssize_t	pad_len;

	bytes = 0;
	if (flags.precision != 0 && len > flags.precision && !flags.numeric)
		len = flags.precision;
	pad_len = flags.width - len;
	if (flags.pad == '0' && (*str == ' ' || *str == '-' || *str == '+') && len--)
		bytes += write(1, str++, 1);
	if (flags.pad == '-')
	{
		bytes += write(1, str, len);
		bytes += ft_dupwrite(' ', pad_len);
	}
	else
	{
		bytes += ft_dupwrite(flags.pad, pad_len);
		bytes += write(1, str, len);	
	}
	return (bytes);
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
			bytes += ft_parse_params(str++, buffer, args);
	}
	va_end(args);
	return (bytes);
}

typedef union u_variadic
{
	int64_t		i;
	uint64_t	u;	// Maybe this should be size_t to work on different platforms
	uintptr_t	p;
	uint8_t		c;	
	char		*s;
}	t_variadic;

// With this, even itoa can work if you pass the flag for integer
// This might not be so interesting, you will have to check the type condition always before checking
// Whereas with separate variables, it's as easy as checking if str==null
int ft_getvar(uint8_t type, va_list args)
{
	t_variadic	var;

	var.u = 0;
	if (type == '%')
		var.c = '%';
	else if (type == 'c')
		var.c = (uint8_t) va_arg(args, int);
	else if (type == 's')
		var.s = (char*) va_arg(args, char*);
	else if (type == 'p')
		var.p = (uintptr_t) va_arg(args, void *);
	else
		var.u = (uint64_t) va_arg(args, unsigned int);
}

#include <stdio.h>
#include <limits.h>

#define test (" %.0.d ", "-")

int main()
{
	ft_printf test;
	printf("\n");
	printf test;
}