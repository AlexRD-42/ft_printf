/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:50:30 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/26 14:20:29 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Performs bitwise manipulation to compute abs of n without overflowing
// array[66] to hold all digits of a 64 bit signed integer with base 2
// Negative sign might not be appropriate for binary or hex
// Mirror changes here to putnbr
char	*ft_itoa(const int64_t number)
{
	const int64_t	sign = (number >> 63);
	char			array[21];
	char			*ptr;
	uint64_t		unumber;

	unumber = (uint64_t) ((number ^ sign) - sign);
	ptr = array + 20;
	*ptr = 0;
	*(--ptr) = sign * (unumber % 10) + '0';
	unumber = sign * (unumber / 10);
	while (unumber != 0)
	{
		*(--ptr) = (unumber % 10) + '0';
		unumber /= 10;
	}
	if (sign == -1)
		*(--ptr) = '-';
	return (ft_strdup(ptr));
}

void	ft_itoa_base(const int64_t number, int fd, const char *base)
{
	const int64_t	sign = (number >> 63);
	char			array[66];
	char			*ptr;
	int64_t			radix;
	uint64_t		unumber;

	radix = 0;
	while (base[radix] != 0)
		radix++;
	if (radix < 2)
		return (NULL);
	unumber = (uint64_t) ((number ^ sign) - sign);
	ptr = array + 65;
	*ptr = 0;
	*(--ptr) = base[(unumber % radix)];
	unumber /= radix;
	while (unumber != 0)
	{
		*(--ptr) = base[(unumber % radix)];
		unumber /= radix;
	}
	if (sign != 0)
		*(--ptr) = '-';
	return (ft_strdup(ptr));
}

// Check: Not necessary to do negative accumulation
int64_t	ft_atoi(const char *num_str)
{
	int64_t	number;
	int64_t	sign;

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

int64_t	ft_atoi_base(const char *str, const char *base)
{
	const char		*start = ft_strpbrk(str, base);
	const int64_t	radix = ft_strlen(base);
	const uint64_t	sign = ((start > str) && (*(start - 1) == '-')) - 1;
	int64_t			number;
	uint8_t			lookup_table[256];

	if (start == NULL || base == NULL || radix < 2)
		return (0);
	ft_memset(lookup_table, 255, 256);
	number = -1;
	while (++number < radix)
		lookup_table[(unsigned char) base[number]] = number;
	number = 0;
	while (*start && lookup_table[(unsigned char) *start] < 255)
		number = number * radix - lookup_table[(unsigned char) *start++];
	return ((number ^ sign) - sign);
}
