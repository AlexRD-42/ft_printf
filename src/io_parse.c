/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:24:49 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/02 16:12:34 by adeimlin         ###   ########.fr       */
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
// And set precision to 0 when its a pointer type
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

int	ft_parse_params(const char *str, const char *end, va_list args)
{
	t_flags		flags;
	size_t		ltable[256];
	const char	*ostr = str;
	char		buffer[MAX_WIDTH];
	char		*ptr;
	// size_t		len;

	ft_memset(ltable, 0, sizeof(ltable));
	ft_memset(buffer, 0, sizeof(buffer));
	while (str < end)
		ltable[(uint8_t)(*str++)] += 1;
	if (ltable['.'] > 1)
		return (0);
	flags = ft_setflags(ostr, *end, ltable);
	ptr = ft_getstr(buffer, flags, args);
	if (flags.type == 'c' || flags.type == '%')
		return (ft_print(ptr, 1, flags));
	else
		return (ft_print(ptr, ft_strlen(ptr), flags));
}
