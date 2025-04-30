/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/30 16:23:45 by adeimlin         ###   ########.fr       */
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
# include <stdarg.h>


typedef struct s_flags
{
	uint8_t	pad; 		// 0: nothing, >0 (-, '0' or space)
	uint8_t	sign; 		// 0: nothing, >0 (+ or space)
	uint8_t	prefix;		// 0: nothing, >0 (x or X)
	size_t	width;
	size_t	precision;
	uint8_t	type;
}	t_flags;

int	ft_print_numeric(uint64_t number, t_flags flags);
int	ft_print_str(char *str, t_flags flags);
int	ft_printf(const char *str, ...);

int64_t	ft_atoi(const char *num_str);
char	*ft_itoa(const int64_t number, const char *base, char *ptr, ssize_t len);
void	*ft_memset(void *dst_void, uint8_t byte, size_t n);
char	*ft_strfind(const char *str, const char *charset, unsigned char ref);
char	*ft_strchr(const char *str, unsigned char c);

#endif