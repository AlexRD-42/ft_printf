/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/02 16:12:21 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_dupwrite(const char c, ssize_t len)
{
	char	buffer[1024];
	int		bytes;

	if (len <= 0)
		return (0);
	bytes = 0;
	ft_memset(buffer, c, sizeof(buffer));
	while (len != 0)
	{
		if (len > 1024)
			bytes += write(1, buffer, 1024);
		else
		{
			bytes += write(1, buffer, len);
			break;
		}
		len -= 1024;
	}
	return (bytes);
}

int	ft_print(char *str, size_t len, t_flags flags)
{
	int		bytes;
	ssize_t	pad_len;

	bytes = 0;
	if (flags.precision != 0 && len > flags.precision && !flags.numeric)
		len = flags.precision;
	pad_len = flags.width - len;
	if (flags.pad == '-')
	{
		bytes = write(1, str, len);
		bytes += ft_dupwrite(' ', pad_len);
	}
	else if (flags.pad == '0')
	{
		if ((*str == ' ' || *str == '-' || *str == '+') && len--)
			bytes = write(1, str++, 1);
		bytes += ft_dupwrite(flags.pad, pad_len);
		bytes += write(1, str, len);
	}
	else
	{
		bytes = ft_dupwrite(flags.pad, pad_len);
		bytes += write(1, str, len);	
	}
	return (bytes);
}

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
			str = ft_strfind(str + 1, "-+#. 0123456789", 0);
			if (str != NULL && ft_strchr("cspdiuxX%", (uint8_t)*str) != NULL)
				bytes += ft_parse_params(ostr, str, args);
			else
				bytes += write(1, ostr, str - ostr);
			str++;
		}
	}
	va_end(args);
	return (bytes);
}


// #include <stdio.h>
// #include <limits.h>

// #define test (" %-s ", "-")

// int main()
// {
// 	ft_printf test;
// 	printf("\n");
// 	printf test;
// }