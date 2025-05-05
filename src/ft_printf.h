/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/05 12:47:18 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef MAX_WIDTH
#  define MAX_WIDTH 4096
# endif

// Includes	and Structs ------------------------------------------------------
# include <stdint.h>
# include <unistd.h>

typedef struct s_flags
{
	uint8_t	pad;		// 0: nothing, >0 (-, '0' or space)
	uint8_t	sign;		// 0: nothing, >0 (+ or space)
	uint8_t	prefix;		// 0: nothing, >0 (x or X)
	uint8_t	dot;
	uint8_t	type;
	uint8_t	numeric;
	size_t	width;
	size_t	precision;
}	t_flags;

int		ft_printf(const char *str, ...);
// utils_io
ssize_t	ft_putnchar(const char c, size_t length);
int64_t	ft_atoi_f(const char *num_str, const char *end);
char	*ft_itoa_f(uint64_t number, const char type, char *ptr, ssize_t length);
// utils_core
size_t	ft_strlen(const char *str);
void	*ft_memset(void *dst_void, uint8_t byte, size_t n);
char	*ft_strfind(const char *str, const char *charset, unsigned char ref);
char	*ft_strchr(const char *str, unsigned char c);
void	*ft_memcpy(void *dst_void, const void *src_void, size_t n);

#endif