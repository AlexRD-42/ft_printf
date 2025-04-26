/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:41:24 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/24 17:40:46 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int32_t	ft_memcmp(const void *addr1_void, const void *addr2_void, size_t data_size)
{
	const uint8_t	*addr1 = (const uint8_t *) addr1_void;
	const uint8_t	*addr2 = (const uint8_t *) addr2_void;

	if (addr1_void == addr2_void)
		return (0);
	while (data_size > 0)
	{
		if (*addr1 != *addr2)
			return (*addr1 - *addr2);
		addr1++;
		addr2++;
		data_size--;
	}
	return (0);
}

int32_t	ft_memrcmp(const void *addr1_void, const void *addr2_void, size_t data_size)
{
	const uint8_t	*addr1 = (const uint8_t *) addr1_void + data_size - 1;
	const uint8_t	*addr2 = (const uint8_t *) addr2_void + data_size - 1;

	if (addr1_void == addr2_void)
		return (0);
	while (data_size > 0)
	{
		if (*addr1 != *addr2)
			return (*addr1 - *addr2);
		addr1--;
		addr2--;
		data_size--;
	}
	return (0);
}
