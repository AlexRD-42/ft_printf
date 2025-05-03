/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:26:18 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/03 18:12:53 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "ft_printf.h"
// This can return ssize_t and could reduce the buffer size
// Is it better to do 2x64 bit operations or 1x128 bit operation
int	ft_dupwrite(const char c, size_t len)
{
	int		bytes;
	char	buffer[256];

	bytes = 0;
	ft_memset(buffer, c, sizeof(buffer));
	while (len >= 256)
	{
		bytes += write(1, buffer, 256);
		len -= 256;
	}
	bytes += write(1, buffer, len);
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

char	*ft_itoa(int64_t number, const char *base, char *ptr, ssize_t len)
{
	int64_t			radix;
	const int64_t	sign = (number > 0) - (number < 0);

	radix = 0;
	while (base[radix] != 0)
		radix++;
	*ptr = 0;
	*(--ptr) = base[sign * (number % radix)];
	number = sign * (number / radix);
	len--;
	while (number != 0)
	{
		*(--ptr) = base[(number % radix)];
		number /= radix;
		len--;
	}
	while (len-- > 0)
		*(--ptr) = '0';
	if (sign < 0)
		*(--ptr) = '-';
	return (ptr);
}

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
		bytes += ft_dupwrite(' ', pad_len);
	}
	else
	{
		bytes += ft_dupwrite(flags.pad, pad_len);
		bytes += write(1, str, len);
	}
	return (bytes);
}
