/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/28 11:32:20 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static va_list	g_args;
static int		g_nbytes;

// Guarantees that there are only valid and non duplicate flags
// Could parse param length and return on digit pos
// Could reduce lines by doing ostr - 1
// Instead of multiplying create an indexed array to return the value
const char	*ft_validate_params(const char *str, t_flags *flags)
{
	size_t			ltable[256];
	const char		*end = ft_strfind(str, "-+#.0123456789", 0);

	if (ft_strchr("cspdiuxX%", (uint8_t)*end) == NULL)
		return (NULL);
	ft_memset(ltable, 0, sizeof(ltable));
	while (str < end)
		ltable[(uint8_t)(*str++)] += 1;
	if (ltable['.'] > 1)
		return (NULL);
	flags->type = *str;
	flags->numeric = ft_strchr("diuxX", (uint8_t) *str) != NULL;
	flags->precision = 0;
	flags->width = 0;
	flags->sign = ' ' * (ltable[' '] && !ltable['+']) + '+' * !!ltable['+'];
	flags->prefix = 'x' * ((ltable['#'] && *str == 'x') || *str == 'p');
	flags->prefix += 'X' * (ltable['#'] && *str == 'X');
	flags->pad = ' ' * (ltable['-'] > 0); // This should be corrected to the left justify behavior properly (if width is set for example)
	return (str);
}

// Receives a ptr to the end of the stack array
char	*ft_itoa64_stack(const int64_t number, const char *base, char *ptr, ssize_t len)
{
	uint64_t		radix;
	uint64_t		abs_num;

	radix = 0;
	while (base[radix] != 0)
		radix++;
	abs_num = (uint64_t)((number ^ (number >> 63)) - (number >> 63));
	*ptr = 0;
	while (abs_num != 0)
	{
		*(--ptr) = base[(abs_num % radix)];
		abs_num /= radix;
		len--;
	}
	while (len-- > 0)
		*(--ptr) = '0';
	if (number < 0)
		*(--ptr) = '-';
	return (ptr);
}

// Goes to the middle of the buffer array, then:
// Backsteps through the array with the number string
// Backsteps more in case of right justify, or expands the midpoint for left justify
void	ft_print_numeric(const char *str, t_flags flags)
{
	char		buffer[MAX_WIDTH];
	char		*ptr;
	char		*end;
	ssize_t		pad_len;

	end = buffer + MAX_WIDTH / 2;
	ptr = end;
	if (flags.type == 'd' || flags.type == 'i')
		ptr = ft_itoa64_stack(va_arg(g_args, int64_t), B_DEC, ptr, flags.precision);
	else if (flags.type == 'u')
		ptr = ft_itoa64_stack(va_arg(g_args, uint64_t), B_DEC, ptr, flags.precision);
	else if (flags.type == 'x')
		ptr = ft_itoa64_stack(va_arg(g_args, uint64_t), B_HEX_LOW, ptr, flags.precision);
	else if (flags.type == 'X')
		ptr = ft_itoa64_stack(va_arg(g_args, uint64_t), B_HEX_UP, ptr, flags.precision);
	else if (flags.type == 'p')
		ptr = ft_itoa64_stack(va_arg(g_args, uint64_t), B_HEX_LOW, ptr, 0);
	if (flags.sign != 0 && *ptr != '-')
		*(--ptr) = flags.sign;
	if (flags.prefix != 0)
	{
		*(--ptr) = flags.prefix;
		*(--ptr) = '0';
	}
	pad_len = end - ptr - flags.width;
	if (flags.pad == '-')
	{
		while (pad_len > 0)
			*end++ = ' ';
	}
	else
	{
		while (pad_len > 0)
			*--ptr = flags.pad;
	}
	g_nbytes = write(1, ptr, end - ptr);
}

void	ft_print_string(const char *str, t_flags flags)
{
	size_t	len;
}

// I won't check for overflows. Because this is stupid.
// Multiple flags are valid. Find digits from mirroring dot pos
const char	*ft_parse_params(const char *str)
{
	t_flags		flags;
	const char	*dot = ft_strchr(str, '.');
	const char	*digit = ft_strfind(str, "123456789", 1);
	const char	*end = ft_validate_params(str, &flags);

	if (end == NULL)
		return (NULL);
	if (flags.pad == 0)
		flags.pad = '0' * ((ft_strchr(str, '0') > digit) && !dot);
	if (dot != NULL)
		flags.precision = ft_atoi(dot + 1);
	if ((digit < dot) || (dot == NULL && digit != NULL))
		flags.width = ft_atoi(digit);
	ft_print_numeric(str, flags);
	return (end + 1);
}

// Returns the number of characters printed
int	ft_printf(const char *str, ...)
{
	const char	*ostr;

	g_nbytes = 0;
    va_start(g_args, str);
	while (*str != 0)
	{
		ostr = str;
		while (*str != 0 && *str != '%')
			str++;
		g_nbytes += write (1, ostr, str - ostr);
		ostr = str;
		if (*str == '%')
			str = ft_parse_params(str + 1);
		if (str == NULL)
			return (1);	// ERROR
	}
}

int main()
{
	ft_printf("%6.5d", 42);
}