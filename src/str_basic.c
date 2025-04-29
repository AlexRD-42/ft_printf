/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:55:34 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/28 11:12:08 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	const char	*ostr;

	ostr = str;
	while (*str != 0)
		str++;
	return (str - ostr);
}

size_t	ft_replace(char *str, unsigned char old_char, unsigned char new_char)
{
	size_t	count;

	count = 0;
	while (*str != 0)
	{
		if (*str == old_char)
		{
			*str = new_char;
			count++;
		}
		str++;
	}
	return (count);
}

int32_t	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 != 0 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *) str1 - *(unsigned char *) str2);
}

int32_t	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0)
	{
		if (*str1 != *str2)
			return (*(unsigned char *) str1 - *(unsigned char *) str2);
		if (*str1 == 0)
			break ;
		str1++;
		str2++;
		n--;
	}
	return (0);
}
