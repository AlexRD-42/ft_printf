/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/30 17:29:36 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_flags	ft_setflags(const char *str, const char type, size_t lut[256])
{
	t_flags		flags;
	const char	*digit = ft_strfind(str, "123456789", 1);
	const char	*dot = ft_strchr(str, '.');
	const char	zero_pad = (ft_strchr(str, '0') < digit) && !dot;

	flags.type = type;
	flags.precision = 0;
	flags.width = 0;
	flags.sign = ' ' * (lut[' '] && !lut['+']) + '+' * !!lut['+'];
	flags.prefix = 'x' * ((lut['#'] && type == 'x') || type == 'p');
	flags.prefix += 'X' * (lut['#'] && type == 'X');
	if (dot != NULL)
		flags.precision = ft_atoi(dot + 1);
	if ((digit < dot) || (dot == NULL && digit != NULL))
		flags.width = ft_atoi(digit);
	flags.pad = ' ' + 13 * (!!lut['-']) + 16 * (!lut['-'] && zero_pad);
	return (flags);
}

static int	ft_parse_params(const char *str, const char *end, va_list args)
{
	t_flags		flags;
	size_t		ltable[256];
	const char	*ostr = str;
	char		c;

	ft_memset(ltable, 0, sizeof(ltable));
	while (str < end)
		ltable[(uint8_t)(*str++)] += 1;
	if (ltable['.'] > 1)
		return (0);
	flags = ft_setflags(ostr, *end, ltable);
	c = '%';
	if (flags.type == 'c')
		c = (char)va_arg(args, int);
	if (flags.type == 'c' || flags.type == '%')
		return (write(1, &c, 1));
	else if (flags.type == 's')
		return (ft_print_str(va_arg(args, char *), flags));
	else if (flags.type == 'd' || flags.type == 'i')
		return (ft_print_numeric(va_arg(args, int), flags));
	else if (flags.type == 'p')
		return (ft_print_numeric((uintptr_t)va_arg(args, void *), flags));
	else
		return (ft_print_numeric(va_arg(args, unsigned int), flags));
}

// Returns the number of characters printed
int	ft_printf(const char *str, ...)
{
	const char	*ostr;
	int			bytes;
	va_list		args;

	bytes = 0;
    va_start(args, str);
	while (*str != 0)
	{
		ostr = str;
		while (*str != 0 && *str != '%')
			str++;
		bytes += write (1, ostr, str - ostr);
		ostr = str;
		if (*str == '%')
		{
			str = ft_strfind(str + 1, "-+#.0123456789", 0);
			if (str == NULL || ft_strchr("cspdiuxX%", (uint8_t)*str) == NULL)
				break ;
			bytes += ft_parse_params(ostr, str, args);
			str++;
		}
	}
	va_end(args);
	return (bytes);
}

#include <stdio.h>
#include <limits.h>

int main()
{
	int num = 42;
	char *str = "pipoca";

	// ft_printf("(%p)", 'a');
	printf(", (%5.5c)", 'a');
}