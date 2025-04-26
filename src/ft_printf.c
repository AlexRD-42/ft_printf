/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/26 15:44:03 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Could create a struct with lookup tables t_lut, which are set in init.
static const char	*g_digits = "0123456789";
static const char	*g_hex_lower = "0123456789abcdef";
static const char	*g_hex_upper = "0123456789ABCDEF";
static const char	*g_format_types = "cspdiuxX%";
static const char	*g_flags = "-+#";

// Guarantees that there are only valid and non duplicate flags
// Could parse param length and return on digit pos
// Could reduce lines by doing ostr - 1
const char	*ft_validate_params(const char *str)
{
	const char	*end = ft_strfind(str, "-+#0123456789", 1);
	uint8_t		char_table[256];

	if (ft_strchr("cspdiuxX%", *end) == NULL)
		return (NULL);
	ft_memset(char_table, 0, sizeof(char_table));
	while (str < end)
		char_table[(uint8_t)(*str++)] = 1;
	return (str);
}

// I won't check for overflows. Because this is stupid.
// Multiple flags are valid. Find digits from mirroring dot pos
const char	*ft_parse_params(const char *str)
{
	t_flags		flags;
	uint8_t		char_table[256];
	const char	*dot = ft_strchr(str, '.');
	const char	*digit = ft_strfind(str, "0123456789", 0);
	const char	*end = ft_validate_params(str);

	if (end == NULL)
		return (NULL);
	flags.type = *end;
	flags.numeric = !!ft_strchr("diuxX", *end);
	flags.precision = 0;
	flags.width = 0;
	flags.sign_pad = !!ft_strchr(str, ' ') + (!!ft_strchr(str, '+') << 1);
	flags.padding = digit != NULL && *digit == '0' && !dot && flags.numeric;
	flags.padding += !!ft_strchr(str, '-') << 1;
	flags.alternate = !!ft_strchr(str, '#');
	if (dot != NULL)
		flags.precision = ft_atoi(dot + 1);
	if ((digit < dot) || (dot == NULL && digit != NULL))
		flags.width = ft_atoi(digit);
	return (end + 1);
}

uint8_t	ft_parse_str(const char *str)
{
	const char	*ostr;

	while (*str != 0)
	{
		ostr = str;
		while (*str != 0 && *str != '%')
			str++;
		write (1, ostr, str - ostr);
		ostr = str;
		if (*str == '%')
			str = ft_parse_params(str);
		if (str - ostr == 0)
			return (1);	// ERROR
	}
}