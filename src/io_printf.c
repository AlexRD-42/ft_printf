/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:09:39 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/27 15:13:59 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa64(const int64_t number, const char *base, size_t len)
{
	char			*ptr;
	uint64_t		radix;
	uint64_t		abs_num;

	radix = 0;
	while (base[radix] != 0)
		radix++;
	ptr = (char *) malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	abs_num = (uint64_t)((number ^ (number >> 63)) - (number >> 63));
	*ptr = 0;
	while (len > (number < 0))
	{
		*(--ptr) = base[(abs_num % radix)];
		abs_num /= radix;
	}
	if (number < 0)
		*(--ptr) = '-';
	return (ptr);
}


