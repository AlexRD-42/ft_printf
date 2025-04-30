/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:26:18 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/30 16:32:23 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char	*ft_itoa(const int64_t number, const char *base, char *ptr, ssize_t len)
{
	uint64_t		radix;
	uint64_t		abs_num;

	radix = 0;
	while (base[radix] != 0)
		radix++;
	abs_num = (uint64_t)((number ^ (number >> 63)) - (number >> 63));
	*ptr = 0;
	if (number == 0)
		*(--ptr) = '0';
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

// Memset is int because of word copying
void	*ft_memset(void *dst_void, uint8_t byte, size_t n)
{
	unsigned char	*dst;

	dst = (unsigned char *) dst_void;
	while (n > 0)
	{
		*dst = byte;
		dst++;
		n--;
	}
	return (dst_void);
}

// When ref == zero, finds first invalid char
// When ref != zero, finds first valid char
char	*ft_strfind(const char *str, const char *charset, unsigned char ref)
{
	unsigned char	lookup_table[256];

	ft_memset(lookup_table, ref, 256);
	while (*charset != 0)
	{
		lookup_table[(unsigned char) *charset] = !ref;
		charset++;
	}
	lookup_table[0] = 0;
	while (lookup_table[(unsigned char) *str] != 0)
		str++;
	if (*str != 0)
		return ((char *) str);
	return (NULL);
}

char	*ft_strchr(const char *str, unsigned char c)
{
	if (c == 0)
	{
		while (*str != 0)
			str++;
		return ((char *) str);
	}
	while (*str != 0)
	{
		if (*str == c)
			return ((char *) str);
		str++;
	}
	return (NULL);
}
