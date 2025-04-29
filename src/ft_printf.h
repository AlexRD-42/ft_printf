/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/28 11:14:00 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MAX_WIDTH 1024
# define B_HEX_UP "0123456789ABCDEF"
# define B_HEX_LOW "0123456789abcdef"
# define B_DEC "0123456789"

// Includes	and Structs ------------------------------------------------------
# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>		// New
# include <limits.h>	// New
# include <stdarg.h>

typedef struct s_flags
{
	uint8_t	pad; 		// 0: nothing, >0 padding character
	uint8_t	sign; 		// 0: nothing, >0 sign character
	uint8_t	prefix;		// 0: nothing, >0 prefix character
	size_t	width;
	size_t	precision;
	uint8_t	type;
	uint8_t	numeric;
}	t_flags;

size_t	ft_strlen(const char *str);
size_t	ft_replace(char *str, unsigned char old_char, unsigned char new_char);
int32_t	ft_strcmp(const char *str1, const char *str2);
int32_t	ft_strncmp(const char *str1, const char *str2, size_t n);

char	*ft_strchr(const char *str, unsigned char c);
char	*ft_strrchr(const char *str, unsigned char c);
char	*ft_strfind(const char *str, const char *charset, uint8_t ref);
char	*ft_strstr(const char *str, const char *substr);
char	*ft_strnstr(const char *str, const char *substr, size_t len);

void	*ft_memset(void *dst_void, uint8_t byte, size_t n);
int32_t	ft_memcmp(const void *addr1_void, const void *addr2_void, size_t data_size);
int32_t	ft_memrcmp(const void *addr1_void, const void *addr2_void, size_t data_size);

char	*ft_itoa(const int64_t number);
void	ft_itoa_base(const int64_t number, int fd, const char *base);
int64_t	ft_atoi(const char *num_str);
int64_t	ft_atoi_base(const char *str, const char *base);

void	ft_putstr(char *str, int fd);
void	ft_putnbr(int64_t n, int fd);
void	ft_putnbr64(const int64_t number, const char *base, int fd, size_t len);

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
