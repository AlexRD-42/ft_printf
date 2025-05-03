0 for idec, 1 for udec, 2 for hex, 3 for HEX
# define B_HEX_UP "0123456789ABCDEF"
# define B_HEX_LOW "0123456789abcdef"
# define B_DEC "0123456789"

// different sizes
static const char	*base[4] = {"0123456789", "0123456789", "0123456789abcdef", "0123456789ABCDEF"};

// would be better to have a function that always uses utoa, 
// gets the absolute value for the integer, and negates before returning
char	*ft_ltoa(int64_t number, uint8_t type, char *ptr, ssize_t len)
{
	int64_t			radix;
	const int64_t	sign = (number > 0) - (number < 0);

	radix = 0;
	while (base[radix] != 0)
		radix++;
	*ptr = 0;
	*(--ptr) = base[sign * (number % radix)];
	number = sign * (number / radix);
	len--;
	while (number != 0)
	{
		*(--ptr) = base[(number % radix)];
		number /= radix;
		len--;
	}
	while (len-- > 0)
		*(--ptr) = '0';
	if (sign < 0)
		*(--ptr) = '-';
	return (ptr);
}