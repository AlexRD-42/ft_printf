# Program name: `libftprintf.a`

# Turn in files Makefile: `*.h, */*.h, *.c, */*.c`
# External functs: `malloc, free, write, va_start, va_arg, va_copy, va_end`

# Mandatory
• Do not implement the original printf()’s buffer management
• Your implementation will be evaluated against the behavior of the original printf()
• You must use the command `ar` to create your library
The use of the libtool command is strictly forbidden
• libftprintf.a must be created at the root of your repository

You have to implement the following conversions:
• `%c` Prints a single character
• `%s` Prints a string (as defined by the common C convention)
• `%p` The void * pointer argument has to be printed in hexadecimal format
• `%d` Prints a decimal (base 10) number
• `%i` Prints an integer in base 10
• `%u` Prints an unsigned decimal (base 10) number
• `%x` Prints a number in hexadecimal (base 16) lowercase format
• `%X` Prints a number in hexadecimal (base 16) uppercase format
• `%%` Prints a percent sign

# Bonus
• Manage any combination of the following flags, and the field minimum width under all conversions
`-` Left Justify
`0` Field is padded with zeroes
`.` Precision specifier
` ` Adds a leading space for positive numbers to align with negative
`+` Always shows a sign, even if it is positive
`#` Special formatting
-----

# To determine
- Is there a difference between d, i, u
- 

# Functions:
- dectohex: returns hex upper case or lower case 
- putnbr_base: `%d %i %u %x %X`
- 

# Pointer checks:
- Size of size_t
- Is it possible to make assumptions based on value?
## Return types:
- (null), string, segfault

