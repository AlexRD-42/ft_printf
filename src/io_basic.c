/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:24:42 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/27 14:00:57 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, int fd)
{
	const char	*ostr = str;

	if (fd == -1 || str == NULL)
		return ;
	while (*str != 0)
		str++;
	write(fd, ostr, str - ostr);
}

// Code duplication for itoa, so far unavoidable
void	ft_putnbr(int64_t n, int fd)
{
	const int8_t	sign = (n >= 0) - (n < 0);
	char			array[21];
	char			*ptr;

	if (fd == -1)
		return ;
	ptr = array + 20;
	*ptr = 0;
	*(--ptr) = sign * (n % 10) + '0';
	n = sign * (n / 10);
	while (n != 0)
	{
		*(--ptr) = (n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		*(--ptr) = '-';
	write(fd, ptr, array + 20 - ptr);
}

// Could make the array 64 by manually null terminating
// Would be two system calls, shit fuck
void	ft_putnbr64(const int64_t number, const char *base, int fd, size_t len)
{
	char		array[66];
	char		*ptr;
	uint64_t	radix;
	uint64_t	abs_num;

	radix = 0;
	while (base[radix] != 0)
		radix++;
	if (radix < 2)
		return (NULL);
	abs_num = (uint64_t)((number ^ (number >> 63)) - (number >> 63));
	ptr = array + 65;
	*ptr = 0;
	*(--ptr) = base[(abs_num % radix)];
	abs_num /= radix;
	while (abs_num != 0)
	{
		*(--ptr) = base[(abs_num % radix)];
		abs_num /= radix;
	}
	if (number < 0)
		*(--ptr) = '-';
	if (len > (array + 65 - ptr) || len == 0)
		len = (array + 65 - ptr);
	write(fd, ptr, len);
}
