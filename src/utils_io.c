/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:26:18 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/05 12:48:56 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

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

int64_t	ft_atoi_f(const char *num_str, const char *end)
{
	int64_t	number;
	int64_t	sign;

	if (num_str == NULL || num_str == end)
		return (0);
	if (end == NULL)
		end = (const char *) UINTPTR_MAX;
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
	while (num_str < end && *num_str >= '0' && *num_str <= '9')
		number = number * 10 - (*num_str++ - '0');
	return (sign * number);
}

char	*ft_itoa_f(uint64_t number, const char f, char *ptr, ssize_t length)
{
	static const char	tbase[2][17] = {"0123456789abcdef", "0123456789ABCDEF"};
	const char			*base = tbase[(f == 'X')];
	const uint_fast8_t	radix = 10 + 6 * (f == 'p' || f == 'X' || f == 'x');
	const uint_fast8_t	sign = (f == 'd' || f == 'i') && (int32_t) number < 0;

	if (sign != 0)
		number = (uint32_t)(-(int64_t)number);
	*ptr = 0;
	while (1)
	{
		*(--ptr) = base[(number % radix)];
		number /= radix;
		length--;
		if (number == 0)
			break ;
	}
	while (length-- > 0)
		*(--ptr) = '0';
	if (sign != 0)
		*(--ptr) = '-';
	return (ptr);
}
