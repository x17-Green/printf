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
		if (*p == '%')
		{
			putchar('%');
			count++;
			continue;
		}
		if (*p == '\0')
		{
			break;
		}
		if (*p == '%' && *(p + 1) == 's' && *(p + 2) == 'n')
		{
			p += 3;
			if (va_arg(args, char *) == NULL)
			{
				count++;
			}
		}
		else
		{
			p++;
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
			case 'i':
			case 'd':
				{
					int d = va_arg(args, int);

					if (d < 0)
					{
						putchar('-');
						d = -d;
						count++;
					}
					if (d == 0)
					{
						putchar('0');
						count++;
					}
					else
					{
						char buffer[20];
						int index = 0, j;
						while (d > 0)
						{
							buffer[index++] = d % 10 + '0';
							d /= 10;
						}
						for (j = index - 1; j >= 0; j--)
						{
							putchar(buffer[j]);
							count++;
						}
					}
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
			case 'o':
				{
					unsigned int u = va_arg(args, unsigned int);

					printf("%o", u);
					break;
				}
			case 'u':
				{
					unsigned int u = va_arg(args, unsigned int);

					printf("%u", u);
					break;
				}
			case 'p':
				{
					void *p = va_arg(args, void *);

					printf("%p", p);
					break;
				}
			case 'x':
			case 'X':
				{
					unsigned int u = va_arg(args, unsigned int);

					printf("%X", u);
					break;
				}
			case 'r':
			case '%':
				{
					putchar('%');
					count++;
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
