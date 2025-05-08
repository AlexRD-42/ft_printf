/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/05/05 17:25:51 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef MAX_WIDTH
#  define MAX_WIDTH 4096
# endif

// Includes	and Structs
# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_flags
{
	char		pad;
	char		sign;
	char		prefix;
	char		dot;
	char		type;
	char		numeric;
	uintptr_t	va_var;
	size_t		width;
	size_t		precision;
}	t_flags;

int		ft_printf(const char *str, ...);
// utils_io
ssize_t	ft_putnchar(const char c, size_t length);
ssize_t	ft_putprefix(char **str, t_flags flags, size_t *length);
int64_t	ft_atoi_f(const char *num_str, const char *end);
char	*ft_itoa_f(uint64_t number, const char f, char *ptr, ssize_t length);
char	*ft_strchr_f(const char *str, unsigned char c, const char *end);
// utils_core
size_t	ft_strlen(const char *str);
void	*ft_memset(void *dst_void, uint8_t byte, size_t n);
char	*ft_strfind(const char *str, const char *charset, unsigned char ref);
char	*ft_strchr(const char *str, unsigned char c);
void	*ft_memcpy(void *dst_void, const void *src_void, size_t n);

#endif