/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:55:12 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/30 19:33:00 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



// Goes to the middle of the buffer array, then:
// Backsteps through the array with the number string
// Backsteps more in case of right justify, or expands the midpoint for left justify
// This handles formats d, i, u, x, X, p
int	ft_print_numeric(uint64_t number, t_flags flags)
{
	char		buffer[MAX_WIDTH];
	char		*ptr;
	char		*end;
	ssize_t		pad_len;

	if (number == 0 && flags.type == 'p')
		return (write(1, "(nil)", 5));
	end = buffer + MAX_WIDTH / 2;
	ptr = end;
	if (flags.type == 'd' || flags.type == 'i')
		ptr = ft_itoa((int64_t)number, B_DEC, ptr, flags.precision);
	else if (flags.type == 'u')
		ptr = ft_utoa(number, B_DEC, ptr, flags.precision);
	else if (flags.type == 'x')
		ptr = ft_utoa(number, B_HEX_LOW, ptr, flags.precision);
	else if (flags.type == 'X')
		ptr = ft_utoa(number, B_HEX_UP, ptr, flags.precision);
	else if (flags.type == 'p')
		ptr = ft_utoa(number, B_HEX_LOW, ptr, 0);
	if (flags.sign != 0 && *ptr != '-')
		*(--ptr) = flags.sign;
	if (flags.prefix != 0)
	{
		*(--ptr) = flags.prefix;
		*(--ptr) = '0';
	}
	pad_len = flags.width - (end - ptr);
	if (flags.pad == '-')
	{
		while (pad_len-- > 0)
			*end++ = ' ';	// Left justify
	}
	else
	{
		while (pad_len-- > 0)
			*--ptr = flags.pad;	// Right justify
	}
	return (write(1, ptr, end - ptr));
}

// Could extract the left justify behavior to work with numbers and strings
int	ft_print_str(char *str, t_flags flags)
{
	int		bytes;
	size_t	len;
	ssize_t	pad_len;

	// if (str == NULL)
	// 	return (write(1, "(null)", 6));
	len = 0;
	while (str[len] != 0)
		len++;
	if (flags.precision != 0 && len > flags.precision)
		len = flags.precision;
	pad_len = flags.width - len;
	if (flags.pad == '-')
	{
		bytes = ft_dupwrite(' ', pad_len);
		bytes += write(1, str, len);
	}
	else
	{
		bytes = write(1, str, len);
		bytes += ft_dupwrite(' ', pad_len);
	}
	return (bytes);
}

// void	ft_justify(const char *str, const char c, size_t str_len, size_t pad_len)
// {
	
// }