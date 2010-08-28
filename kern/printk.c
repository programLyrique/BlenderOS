#include "printk.h"
#include "../utils/arg.h"//Créer un starg spécialement pour BlenderOS

//Enlever la récursivité ?
void printk(const char *format, ...)
{
	va_list	ap;

	char buf[16];
	int	i, j, size, buflen, neg;

	unsigned	char c;
	int		ival;
	unsigned int	uival;

	va_start(ap, format);

	while ((c = *format++)) {
		size = 0;
		neg  = 0;

		if (c == 0)
			break;
		else if (c == '%') {
			c = *format++;
			if (c >= '0' && c <= '9') {
				size = c - '0';
				c = *format++;
			}

			if (c == 'd') {
				ival = va_arg(ap, int);
				if (ival < 0) {
					uival = 0 - ival;
					neg++;
				}
				else
					uival = ival;
				itoa(buf, uival, 10);

				buflen = strlen(buf);
				if (buflen < size)
					for (i=size, j=buflen; i>=0; i--, j--)
						buf[i] = (j>=0) ? buf[j] : '0';

				if (neg)
					printk("-%s", buf);
				else
					printk(buf);
			}
			else if (c == 'u') {
				uival = va_arg(ap, int);
				itoa(buf, uival, 10);

				buflen = strlen(buf);
				if (buflen < size)
					for (i=size, j=buflen; i>=0; i--, j--)
						buf[i] = (j>=0) ? buf[j] : '0';

					printk(buf);
			}
			else if (c == 'x' || c == 'X') {
				uival = va_arg(ap, int);
				itoa(buf, uival, 16);

				buflen = strlen(buf);
				if (buflen < size)
					for (i=size, j=buflen; i>=0; i--, j--)
						buf[i] = (j>=0) ? buf[j] : '0';

					printk("0x%s", buf);
			}
			else if (c == 'p') {
				uival = va_arg(ap, int);
				itoa(buf, uival, 16);
				size = 8;

				buflen = strlen(buf);
				if (buflen < size)
					for (i=size, j=buflen; i>=0; i--, j--)
						buf[i] = (j>=0) ? buf[j] : '0';

					printk("0x%s", buf);
			}
			else if (c == 's') {
				printk( (char *) va_arg(ap, int) );
			}
			else {
			}
		}
		else
			putchar(c);
	}

	return;
}
