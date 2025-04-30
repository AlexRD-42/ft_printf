#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int64_t	ft_atoi(const char *num_str)
{
	int64_t	number;
	int64_t	sign;

	if (num_str == NULL)
		return (0);
	number = 0;
	sign = -1;
	while (*num_str == 32 || (*num_str >= 9 && *num_str <= 13))
		num_str++;
	if (*num_str == '-')
	{
		num_str++;
		sign = -sign;
	}
	else if (*num_str == '+')
		num_str++;
	while (*num_str >= '0' && *num_str <= '9')
		number = number * 10 - (*num_str++ - '0');
	return (sign * number);
}

int	main(void)
{
	printf("(%10d)", -42);
}