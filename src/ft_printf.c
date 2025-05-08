/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/05 17:26:22 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_flags	ft_setflags(const char *str, const char type, const char *end)
{
	t_flags		flags;
	const char	*digit = ft_strfind(str, "123456789", 1);
	const char	*dot = ft_strchr_f(str, '.', end);
	const char	zpad = !!ft_strchr_f(str, '0', end)
		&& (ft_strchr_f(str, '0', end) < digit);
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
	flags.pad += 16 * (!lut[45] && zpad && flags.numeric && !dot);
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

static int	ft_write_f(char *str, size_t len, t_flags flags)
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
		if (*str != '(' && flags.pad == '0')
			bytes += ft_putprefix(&str, flags, &len);
		bytes += ft_putnchar(flags.pad, pad_len);
		bytes += write(1, str, len);
	}
	return (bytes);
}

static int	ft_parse(const char *str, const char *end, va_list args)
{
	char		buffer[MAX_WIDTH];
	char		*ptr;
	t_flags		flags;
	size_t		len;

	flags = ft_setflags(str, *end, end);
	if (flags.dot > 1 || ft_strchr("cspdiuxX", *(uint8_t *)end) == NULL)
		return (write(1, str, end - str));
	ft_memset(buffer, 0, sizeof(buffer));
	if (flags.type == 's' || flags.type == 'p')
		flags.va_var = (uintptr_t) va_arg(args, void *);
	else
		flags.va_var = va_arg(args, unsigned int);
	ptr = ft_getstr(buffer, flags.va_var, flags);
	len = 1;
	if (flags.type != 'c')
		len = ft_strlen(ptr);
	if (flags.type == 's' && flags.dot != 0 && flags.precision < len)
		len = flags.precision;
	if (flags.numeric && flags.dot && flags.precision < len && !flags.va_var)
		len = flags.precision + (flags.sign != 0 || *str == '-');
	if (flags.type == 's' && flags.dot && flags.precision < 6 && !flags.va_var)
		len = 0;
	return (ft_write_f(ptr, len, flags));
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
		bytes += write(1, ostr, str - ostr);
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
