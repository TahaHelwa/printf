#include "main.h"

/**
 * _printf - produces output according to a format.
 * @format: A character string containing zero or more directives
 * Return: the number of characters printed (excluding the null byte used to end output to strings)
 */
int _printf(const char *format, ...)
{
	int num_chars_printed = 0;
	va_list args;
	char buffer[1024];
	int buffer_index = 0;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'c':
					buffer[buffer_index++] = va_arg(args, int);
					break;
				case 's':
					buffer_index += snprintf(buffer + buffer_index, 1024 - buffer_index, "%s", va_arg(args, char *));
					break;
				case '%':
					buffer[buffer_index++] = '%';
					break;
				case 'd':
				case 'i':
					buffer_index += snprintf(buffer + buffer_index, 1024 - buffer_index, "%d", va_arg(args, int));
					break;
				case 'u':
					buffer_index += snprintf(buffer + buffer_index, 1024 - buffer_index, "%u", va_arg(args, unsigned int));
					break;
				case 'o':
					buffer_index += snprintf(buffer + buffer_index, 1024 - buffer_index, "%o", va_arg(args, unsigned int));
					break;
				case 'x':
					buffer_index += snprintf(buffer + buffer_index, 1024 - buffer_index, "%x", va_arg(args, unsigned int));
					break;
				case 'X':
					buffer_index += snprintf(buffer + buffer_index, 1024 - buffer_index, "%X", va_arg(args, unsigned int));
					break;
				case 'b':
					buffer_index += binary_to_buffer(va_arg(args, unsigned int), buffer + buffer_index);
					break;
				case 'S':
					buffer_index += string_to_buffer(va_arg(args, char*), buffer + buffer_index);
					break;
				case 'p':
					buffer_index += snprintf(buffer + buffer_index, 1024 - buffer_index, "%p", va_arg(args, void *));
					break;
				case 'r':
					buffer_index += reverse_string_to_buffer(va_arg(args, char*), buffer + buffer_index);
					break;
				case 'R':
					buffer_index += rot13_string_to_buffer(va_arg(args, char*), buffer + buffer_index);
					break;
				default:
					buffer[buffer_index++] = '%';
					buffer[buffer_index++] = *format;
					break;
			}
		}
		else
		{
			buffer[buffer_index++] = *format;
		}
		format++;

		if (buffer_index >= 1024)
			{
				write(STDOUT_FILENO, buffer, buffer_index);
				num_chars_printed += buffer_index;
				buffer_index = 0;
			}
	}

	write(STDOUT_FILENO, buffer, buffer_index);
	num_chars_printed += buffer_index;

	va_end(args);

	return num_chars_printed;
}

/**
 * binary_to_buffer - converts an unsigned int to binary and writes it to a buffer
 * @num: the number to convert
 * @buffer: the buffer to write to
 * Return: the number of characters written to the buffer
 */
int binary_to_buffer(unsigned int num, char *buffer)
{
	if (num / 2)
		binary_to_buffer(num / 2, buffer);
	*buffer = (num % 2) + '0';
	return 1;
}

/**
 * string_to_buffer - writes a string to a buffer, replacing non-printable characters with their hex codes
 * @str: the string to write
 * @buffer: the buffer to write to
 * Return: the number of characters written to the buffer
 */
int string_to_buffer(char *str, char *buffer)
{
	int num_chars_written = 0;
	int i = 0;

	while (str[i])
	{
		if (str[i] < 32 || str[i] >= 127)
		{
			num_chars_written += sprintf(buffer + num_chars_written, "\\x%02X", str[i]);
		}
		else
		{
			buffer[num_chars_written++] = str[i];
		}
		i++;
	}

	return num_chars_written;
}

/**
 * reverse_string_to_buffer - reverses a string and writes it to a buffer
 * @str: the string to reverse and write
 * @buffer: the buffer to write to
 * Return: the number of characters written to the buffer
 */
int reverse_string_to_buffer(char *str, char *buffer)
{
	int num_chars_written = 0;
	int i = 0;
	int len = strlen(str);

	while (i < len)
	{
		buffer[num_chars_written++] = str[len - i - 1];
		i++;
	}

	return num_chars_written;
}

/**
 * rot13_string_to_buffer - applies the rot13 transformation to a string and writes it to a buffer
 * @str: the string to apply the rot13 transformation to and write
 * @buffer: the buffer to write to
 * Return: the number of characters written to the buffer
 */
int rot13_string_to_buffer(char *str, char *buffer)
{
	int num_chars_written = 0;
	int i = 0;

	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			buffer[num_chars_written++] = ((str[i] - 'a' + 13) % 26) + 'a';
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			buffer[num_chars_written++] = ((str[i] - 'A' + 13) % 26) + 'A';
		}
		else
		{
			buffer[num_chars_written++] = str[i];
		}
		i++;
	}

	return num_chars_written;
}
