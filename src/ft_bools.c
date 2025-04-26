/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:03:50 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/24 16:51:51 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int8_t	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int8_t	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int8_t	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int8_t	ft_isascii(int c)
{
	return (!(c >> 7));
}

int8_t	ft_isformat_type(uint8_t c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%');
}
