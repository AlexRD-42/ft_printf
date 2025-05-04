/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:26:18 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/04 11:05:09 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "ft_printf.h"

ssize_t	ft_putnchar(const char c, size_t length)
{
	ssize_t		bytes;
	const char	buffer[64] = {c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};

	bytes = 0;
	while (length >= 64)
	{
		bytes += write(1, buffer, 64);
		length -= 64;
	}
	bytes += write(1, buffer, length);
	return (bytes);
}

int64_t	ft_atoi(const char *num_str)
{
	int64_t	number;
	int64_t	sign;

	if (num_str == NULL)
		return (0);
	number = 0;
	sign = -1;
	while (*num_str == 32 || (*num_str >= 9 && *num_str <= 13))
		num_str++;
	if (*num_str == '-')
	{
		num_str++;
		sign = -sign;
	}
	else if (*num_str == '+')
		num_str++;
	while (*num_str >= '0' && *num_str <= '9')
		number = number * 10 - (*num_str++ - '0');
	return (sign * number);
}

// This could zero pad as well
char	*ft_utoa(uint64_t number, const char *base, char *ptr, ssize_t len)
{
	uint64_t		radix;

	radix = 0;
	while (base[radix] != 0)
		radix++;
	*ptr = 0;
	*(--ptr) = base[(number % radix)];
	number /= radix;
	len--;
	while (number != 0)
	{
		*(--ptr) = base[(number % radix)];
		number /= radix;
		len--;
	}
	while (len-- > 0)
		*(--ptr) = '0';
	return (ptr);
}

int	ft_print(char *str, size_t len, t_flags flags)
{
	int		bytes;
	size_t	pad_len;

	bytes = 0;
	pad_len = 0;
	if (flags.dot != 0 && len > flags.precision && !flags.numeric)
		len = flags.precision;
	if (len < flags.width)
		pad_len = flags.width - len;
	if (flags.pad == '0' && (*str == 32 || *str == 45 || *str == 43) && len--)
		bytes += write(1, str++, 1);
	if (flags.pad == '-')
	{
		bytes += write(1, str, len);
		bytes += ft_putnchar(' ', pad_len);
	}
	else
	{
		bytes += ft_putnchar(flags.pad, pad_len);
		bytes += write(1, str, len);
	}
	return (bytes);
}
