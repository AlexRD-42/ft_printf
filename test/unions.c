typedef union u_variadic
{
	int64_t		i;
	uint64_t	u;	// Maybe this should be size_t to work on different platforms
	uintptr_t	p;
	uint8_t		c;	
	char		*s;
}	t_variadic;

// With this, even itoa can work if you pass the flag for integer
// This might not be so interesting, you will have to check the type condition always before checking
// Whereas with separate variables, it's as easy as checking if str==null
int ft_getvar(uint8_t type, va_list args)
{
	t_variadic	var;

	var.u = 0;
	if (type == '%')
		var.c = '%';
	else if (type == 'c')
		var.c = (uint8_t) va_arg(args, int);
	else if (type == 's')
		var.s = (char*) va_arg(args, char*);
	else if (type == 'p')
		var.p = (uintptr_t) va_arg(args, void *);
	else
		var.u = (uint64_t) va_arg(args, unsigned int);
}