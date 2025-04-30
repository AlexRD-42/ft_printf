/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:24:49 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/30 19:32:27 by adeimlin         ###   ########.fr       */
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
	if (dot != NULL && type != 'p') // this was changed
		flags.precision = ft_atoi(dot + 1);
	if ((digit < dot) || (dot == NULL && digit != NULL))
		flags.width = ft_atoi(digit);
	flags.pad = ' ' + 13 * (!!lut['-']) + 16 * (!lut['-'] && zero_pad);
	return (flags);
}

// To do: index this disaster with a lut for the bases
// And set precision to 0 when its a pointer type
static char	*ft_get_nstr(char *ptr, t_flags flags, va_list args)
{
	uint64_t	number;

	if (flags.type == 'p')
		number = (uintptr_t) va_arg(args, void *);
	else
		number = va_arg(args, unsigned int);
	if (flags.type == 'p' && number == 0)
	{
		ft_memcpy(ptr - 6, "(nil)", 6);
		return (ptr - 6);
	}
	if (flags.type == 'd' || flags.type == 'i')
		ptr = ft_itoa((int)number, B_DEC, ptr, flags.precision);
	else if (flags.type == 'u')
		ptr = ft_utoa(number, B_DEC, ptr, flags.precision);
	else if (flags.type == 'x')
		ptr = ft_utoa(number, B_HEX_LOW, ptr, flags.precision);
	else if (flags.type == 'X')
		ptr = ft_utoa(number, B_HEX_UP, ptr, flags.precision);
	else if (flags.type == 'p')
		ptr = ft_utoa(number, B_HEX_LOW, ptr, 0);
	if (flags.sign != 0 && *ptr != '-')
		*(--ptr) = flags.sign;
	if (flags.prefix != 0)
	{
		*(--ptr) = flags.prefix;
		*(--ptr) = '0';
	}
	return (ptr);
}

int	ft_parse_params(const char *str, const char *end, va_list args)
{
	t_flags		flags;
	size_t		ltable[256];
	const char	*ostr = str;
	static char	buffer[MAX_WIDTH];
	char		*ptr;

	ptr = buffer;
	ft_memset(ltable, 0, sizeof(ltable));
	*ptr = '%';
	while (str < end)
		ltable[(uint8_t)(*str++)] += 1;
	if (ltable['.'] > 1)
		return (0);
	flags = ft_setflags(ostr, *end, ltable);
	if (ft_strchr("diuxXp", flags.type) != NULL)
		ptr = ft_get_nstr(ptr + MAX_WIDTH, flags, args);
	else if (flags.type == 'c')
		*ptr = (char)va_arg(args, int);
	else if (flags.type == 's')
		ptr = (char*)va_arg(args, char*);
	if (ptr == NULL)
		ptr = ft_memcpy(buffer, "(null)", 7);
	if (flags.type == 'c' || flags.type == '%')
		return (ft_print(ptr, 1, flags));
	else
		return (ft_print(ptr, ft_strlen(ptr), flags));
}
