/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:50:30 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/30 12:28:52 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Performs bitwise manipulation to compute abs of n without overflowing
// array[66] to hold all digits of a 64 bit signed integer with base 2
// Negative sign might not be appropriate for binary or hex
// Mirror changes here to putnbr
// char	*ft_itoa(const int64_t number)
// {
// 	const int64_t	sign = (number >> 63);
// 	char			array[21];
// 	char			*ptr;
// 	uint64_t		unumber;

// 	unumber = (uint64_t) ((number ^ sign) - sign);
// 	ptr = array + 20;
// 	*ptr = 0;
// 	*(--ptr) = sign * (unumber % 10) + '0';
// 	unumber = sign * (unumber / 10);
// 	while (unumber != 0)
// 	{
// 		*(--ptr) = (unumber % 10) + '0';
// 		unumber /= 10;
// 	}
// 	if (sign == -1)
// 		*(--ptr) = '-';
// 	return (ft_strdup(ptr));
// }

// void	ft_itoa_base(const int64_t number, int fd, const char *base)
// {
// 	const int64_t	sign = (number >> 63);
// 	char			array[66];
// 	char			*ptr;
// 	int64_t			radix;
// 	uint64_t		unumber;

// 	radix = 0;
// 	while (base[radix] != 0)
// 		radix++;
// 	if (radix < 2)
// 		return (NULL);
// 	unumber = (uint64_t) ((number ^ sign) - sign);
// 	ptr = array + 65;
// 	*ptr = 0;
// 	*(--ptr) = base[(unumber % radix)];
// 	unumber /= radix;
// 	while (unumber != 0)
// 	{
// 		*(--ptr) = base[(unumber % radix)];
// 		unumber /= radix;
// 	}
// 	if (sign != 0)
// 		*(--ptr) = '-';
// 	return (ft_strdup(ptr));
// }

// int64_t	ft_atoi_base(const char *str, const char *base)
// {
// 	const char		*start = ft_strpbrk(str, base);
// 	const int64_t	radix = ft_strlen(base);
// 	const uint64_t	sign = ((start > str) && (*(start - 1) == '-')) - 1;
// 	int64_t			number;
// 	uint8_t			lookup_table[256];

// 	if (start == NULL || base == NULL || radix < 2)
// 		return (0);
// 	ft_memset(lookup_table, 255, 256);
// 	number = -1;
// 	while (++number < radix)
// 		lookup_table[(unsigned char) base[number]] = number;
// 	number = 0;
// 	while (*start && lookup_table[(unsigned char) *start] < 255)
// 		number = number * radix - lookup_table[(unsigned char) *start++];
// 	return ((number ^ sign) - sign);
// }

// void	ft_putnbr64(const int64_t number, const char *base, int fd, size_t len)
// {
// 	char		array[66];
// 	char		*ptr;
// 	uint64_t	radix;
// 	uint64_t	abs_num;

// 	radix = 0;
// 	while (base[radix] != 0)
// 		radix++;
// 	if (radix < 2)
// 		return (NULL);
// 	abs_num = (uint64_t)((number ^ (number >> 63)) - (number >> 63));
// 	ptr = array + 65;
// 	*ptr = 0;
// 	*(--ptr) = base[(abs_num % radix)];
// 	abs_num /= radix;
// 	while (abs_num != 0)
// 	{
// 		*(--ptr) = base[(abs_num % radix)];
// 		abs_num /= radix;
// 	}
// 	if (number < 0)
// 		*(--ptr) = '-';
// 	if (len > (array + 65 - ptr) || len == 0)
// 		len = (array + 65 - ptr);
// 	write(fd, ptr, len);
// }
