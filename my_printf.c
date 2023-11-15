#include "main.h"

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
int _printf(const char *format, ...)
{
	int i;
	va_list args;

	va_start(args, format);

	for (i = 0; format[i]; i++)
	{
		if (format[i] != '%')
		{
			putchar(format[i]);
			continue;
		}
		if (format[i] == '\0')
		{
			break;
		}
		if (format[i] == '%')
		{
			putchar('%');
			continue;
		}

		switch (format[++i])
		{
			case 'c':
				{
					char c = (char) va_arg(args, int);

					putchar(c);
					break;
				}
			case 's':
				{
					char *s = va_arg(args, char *);

					printf("%s", s);
					break;
				}
			default:
				{
					printf("%%%c", format[i]);
					break;
				}
		}
	}
	va_end(args);
	return (format[i]);
}
