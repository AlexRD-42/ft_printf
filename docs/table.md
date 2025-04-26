%[flags][width][.precision][length][specifier]

## Specifiers:
`c 99`: char
`s 115`: string, (null) 
`p 112`: 0x38ABDFKe
`d 100`: 255
`i 105`: Prints an integer in base 10
`u 117`: Prints an unsigned decimal (base 10) number
`x 120`: ff
`X 88`: FF
`% 37`: Prints a percent sign

## Flags
`0` Zero padding will be true if the number 0 showed before other digits
`-` Left Justify, must come before the width specifier
`+` Force sign, must come before the width specifier
` ` Leading space for positive numbers, must come before the width specifier
`.` Truncation, will determine how many characters are shown (to determine if prefixes like 0x count)
`#` Alternative form, for this project adds a prefix to hex formats (`0x` or `0X`)


## Ideas:
- If both `0` and `-` are specified, `0` is ignored
- If both `0` and `.` are specified, `0` is ignored
- If both ` ` and `+` are specified, ` ` is ignored
- The # flag combined with 0 and width will pad after the 0x prefix: %#010x
- Maximum length of flags before digits is 5


## Invalid
- % followed by non-specifier and non-digit is invalid

# Functions
- Putnstr
- strnpbrk