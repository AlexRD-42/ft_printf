/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/26 13:15:34 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// Includes	and Structs ------------------------------------------------------
# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>		// New
# include <limits.h>	// New
# include <math.h>		// New

typedef struct s_flags
{
	uint8_t	padding; 	// 0: nothing, 1: zero padding,  >1: left justify
	uint8_t	sign_pad; 	// 0: nothing, 1: leading space, >1: force sign
	uint8_t	alternate;
	size_t	width;
	size_t	precision;
	uint8_t	type;
	uint8_t	numeric;
}	t_flags;

char	*ft_strchr(const char *str, unsigned char c);
void	*ft_memset(void *dst_void, uint8_t byte, size_t n);
char	*ft_strfind(const char *str, const char *charset, uint8_t byte);
int64_t	ft_atoi(const char *num_str);
// Parsing rule:
// Find format specifier: (strnpbrk) "cspdiux%"
// Read until either type or null is found, or until invalid

// Find first digit (strnpbrk): "0123456789", then zero_padding = true;

// Have a num_str[2] initialized to zero
// When you find a '.', set precision to 1 and always index num_str by precision
// This will make it so that num_str[1] is always the precision
// Then find first digit or '.', and if the previous char is a '.', increase the index of your numstr




// Then read flags like normal, their order won't matter
#endif
