/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:24:42 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/26 15:30:16 by adeimlin         ###   ########.fr       */
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

void	ft_itoa_base(const int64_t number, int fd, const char *base)
{
	const int64_t	sign = (number >> 63);
	char			array[66];
	char			*ptr;
	int64_t			radix;
	uint64_t		abs_num;

	radix = 0;
	while (base[radix] != 0)
		radix++;
	if (radix < 2)
		return (NULL);
	abs_num = (uint64_t) ((number ^ sign) - sign);
	ptr = array + 65;
	*ptr = 0;
	*(--ptr) = base[(abs_num % radix)];
	abs_num /= radix;
	while (abs_num != 0)
	{
		*(--ptr) = base[(abs_num % radix)];
		abs_num /= radix;
	}
	if (sign != 0)
		*(--ptr) = '-';
	write(fd, ptr, array + 20 - ptr);
}