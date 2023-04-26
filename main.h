#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

int _putchar(char c);
int _printf(const char *format, ...);
int print_char(va_list arg);
int print_string(va_list arg);
int print_percent(va_list arg);
int print_integer(va_list arg);
int print_binary(va_list arg);
int print_unsigned(va_list arg);
int print_octal(va_list arg);
int print_hex(va_list arg);
int print_HEX(va_list arg);
int print_reverse(va_list arg);
int print_rot13(va_list arg);
int print_pointer(va_list arg);

/**
 * struct specifier - Struct for data types and their functions
 * @type: The type of data type
 * @func: The function pointer to the corresponding function
 */
typedef struct specifier
{
	char *type;
	int (*func)(va_list);
} specifier_t;

#endif /* MAIN_H */
