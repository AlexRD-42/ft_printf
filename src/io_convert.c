/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:26:35 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/30 19:45:27 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
