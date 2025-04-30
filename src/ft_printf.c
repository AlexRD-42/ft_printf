/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/30 19:42:09 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_dupwrite(const char c, ssize_t len)
{
	char			buffer[1024];
	const ssize_t	olen = len;

	if (len <= 0)
		return (0);
	ft_memset(buffer, c, sizeof(buffer));
	while (len != 0)
	{
		if (len > 1024)
			write(1, buffer, 1024);
		else
		{
			write(1, buffer, len);
			break;
		}
		len -= 1024;
	}
	return ((ssize_t) olen);
}

int	ft_print(char *str, size_t len, t_flags flags)
{
	int		bytes;
	ssize_t	pad_len;

	if (flags.precision != 0 && len > flags.precision)
		len = flags.precision;
	pad_len = flags.width - len;
	if (flags.pad == '-')
	{
		bytes = ft_dupwrite(' ', pad_len);
		bytes += write(1, str, len);
	}
	else
	{
		bytes = write(1, str, len);
		bytes += ft_dupwrite(' ', pad_len);
	}
	return (bytes);	
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

// #include <stdio.h>
// #include <limits.h>

// #define test "%p", 0
// int main()
// {
// 	int num = 42;
// 	char *str = "";

// 	ft_printf(test);
// 	printf("\n");
// 	printf(test);
// }