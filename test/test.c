#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

ssize_t	ft_putnchar(const char c, size_t length)
{
	ssize_t			bytes;
	const int64_t	word = 0x0101010101010101 * c;
	const int64_t	cache[8] = {word, word, word, word, word, word, word, word};

	bytes = 0;
	while (length >= 256)
	{
		bytes += write(1, cache, 256);
		length -= 256;
	}
	bytes += write(1, cache, length);
	return (bytes);
}

int	main(void)
{
	int bytes = 0;
	bytes = printf("(%10d)");
}