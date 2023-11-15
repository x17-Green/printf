#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>

/* Function Declarations */
void cleanup(va_list args, char *output);
int _printf(const char *format, ...);

/* Function Definitions */

/**
 * cleanup - Peforms cleanup operations for _printf.
 * @args: A va_list of arguments provided to _printf.
 * @output: A char pointer containing the output.
 */
void cleanup(va_list args, char *output)
{
    va_end(args);
    fwrite(output, 1, strlen(output), stdout);
    free(output);
}
/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
__attribute__((format(printf, 1, 2)))
int _printf(const char *format, ...)
{
	const char *p;
	int count;

	va_list args;
	va_start(args, format);

	count = 0;

	for (p = format; *p; ++p)
	{
		if (*p != '%')
		{
			putchar(*p);
			count++;
			continue;
		}
		++p;
		if (*p == '\0')
		{
			break;
		}
		if (*p == '%')
		{
			putchar('%');
			count++;
			continue;
		}

		switch (*p)
		{
			case 'c':
				{
					char c = (char) va_arg(args, int);

					putchar(c);
					count++;
					break;
				}
			case 's':
				{
					const char *s = va_arg(args, char *);

					while (*s)
					{
						putchar(*s);
						count++;
						s++;
					}
					break;
				}
			default:
				{
					printf("%%%c", *p);
					break;
				}
		}
	}
	va_end(args);
	return (count);
}
