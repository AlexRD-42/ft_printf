/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/04 10:45:10 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef MAX_WIDTH
#  define MAX_WIDTH 4096
# endif

# define B_HEX_UP "0123456789ABCDEF"
# define B_HEX_LOW "0123456789abcdef"
# define B_DEC "0123456789"

// Includes	and Structs ------------------------------------------------------
# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_flags
{
	uint8_t	pad;		// 0: nothing, >0 (-, '0' or space)
	uint8_t	sign;		// 0: nothing, >0 (+ or space)
	uint8_t	prefix;		// 0: nothing, >0 (x or X)
	size_t	width;
	uint8_t	base_index;
	size_t	precision;
	uint8_t	dot;
	uint8_t	type;
	uint8_t	numeric;
}	t_flags;

int		ft_printf(const char *str, ...);
// utils_io
ssize_t	ft_putnchar(const char c, size_t length);
char	*ft_utoa(uint64_t number, const char *base, char *ptr, ssize_t len);
char	*ft_itoa(const int64_t nbr, const char *base, char *ptr, ssize_t len);
int64_t	ft_atoi(const char *num_str);
int		ft_print(char *str, size_t len, t_flags flags);
// utils_core
size_t	ft_strlen(const char *str);
void	*ft_memset(void *dst_void, uint8_t byte, size_t n);
char	*ft_strfind(const char *str, const char *charset, unsigned char ref);
char	*ft_strchr(const char *str, unsigned char c);
void	*ft_memcpy(void *dst_void, const void *src_void, size_t n);

#endif