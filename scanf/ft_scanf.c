#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

/* Skip whitespace in input */
int match_space(FILE *f)
{
    int c;
    while ((c = fgetc(f)) != EOF)
    {
        if (!isspace(c))
        {
            ungetc(c, f);
            return 0;
        }
    }
    return -1;
}

/* Match a literal character */
int match_char(FILE *f, char c)
{
    int input = fgetc(f);
    if (input == c)
        return 1;
    if (input != EOF)
        ungetc(input, f);
    return 0;
}

/* Read one character (including spaces) */
int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
    if (c == EOF)
        return 0;

    char *ptr = va_arg(ap, char *);
    *ptr = (char)c;
    return 1;
}

/* Read integer */
int scan_int(FILE *f, va_list ap)
{
    int c;
    int sign = 1;
    int result = 0;
    int found_digit = 0;

    c = fgetc(f);
    if (c == '-' || c == '+')
    {
        if (c == '-')
            sign = -1;
    }
    else
        ungetc(c, f);

    while ((c = fgetc(f)) != EOF && isdigit(c))
    {
        found_digit = 1;
        result = result * 10 + (c - '0');
    }

    if (c != EOF)
        ungetc(c, f);

    if (!found_digit)
        return 0;

    int *ptr = va_arg(ap, int *);
    *ptr = result * sign;
    return 1;
}

/* Read string (non-whitespace sequence) */
int scan_string(FILE *f, va_list ap)
{
    int c;
    char *str = va_arg(ap, char *);
    int i = 0;

    while ((c = fgetc(f)) != EOF && !isspace(c))
    {
        str[i++] = c;
    }

    if (c != EOF)
        ungetc(c, f);

    if (i == 0)
        return 0;

    str[i] = '\0';
    return 1;
}

/* Conversion dispatcher */
int match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format)
    {
        case 'c':
            return scan_char(f, ap);
        case 'd':
            match_space(f);
            return scan_int(f, ap);
        case 's':
            match_space(f);
            return scan_string(f, ap);
        default:
            return -1;
    }
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;

    int c = fgetc(f);
    if (c == EOF)
        return EOF;
    ungetc(c, f);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (match_conv(f, &format, ap) != 1)
                break;
            nconv++;
        }
        else if (isspace(*format))
        {
            if (match_space(f) == -1)
                break;
        }
        else if (match_char(f, *format) != 1)
            break;
        format++;
    }

    if (ferror(f))
        return EOF;

    return nconv;
}

int ft_scanf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}
