#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_flags
{
	int padding;
	int precision;
}				t_flags;
int ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}
void ft_putchar(char c)
{
	write(1, &c, 1);
}
int ft_putnchar(char c, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}
int ft_atoi(const char *str)
{
	int nb;
	int i;

	i = 0;
	nb = 0;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}
int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
int ft_nbrlen(int nb)
{
	int i;
	unsigned int n;

	n = nb < 0 ? -nb : nb;
	i = 0;
	if (nb == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int ft_hexlen(unsigned int nb)
{
	int i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		i++;
	}
	return (i);
}
void ft_putnbr(int nb)
{
	unsigned int n;

	n = nb < 0 ? -nb : nb;
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');

}
void ft_putnbrbase(unsigned int nb, char *base)
{
	if (nb >= 16)
	{
		ft_putnbrbase(nb / 16, base);
		ft_putnbrbase(nb % 16, base);
	}
	else
		ft_putchar(base[nb]);
}
int ft_strchr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int ft_width(t_flags *flags, const char *str)
{
	int i;

	i = 0;
	flags->padding = ft_atoi(str);
	while (ft_isdigit(str[i]))
		i++;
	return(i);
}
int ft_precision(t_flags *flags, const char *str)
{
	int i;

	i = 0;
	flags->precision = ft_atoi(str);
	while (ft_isdigit(str[i]))
		i++;
	return(i);
}
void init_flags(t_flags *flags)
{
	flags->padding = 0;
	flags->precision = -1;
}
int ft_flags(t_flags *flags, const char *str)
{
	int i;
	i = 1;
	init_flags(flags);
	while (ft_strchr("0123456789.",str[i]))
	{
		if (ft_isdigit(str[i]))
			i += ft_width(flags, &(str[i]));
		else if (str[i] == '.')
		{
			i++;
			i += ft_precision(flags, &(str[i]));
		}
	}
	return (i);
}
int put_d(t_flags *flags, va_list param)
{
	int i;
	int nb;
	int len;

	i = 0;
	nb = (int)va_arg(param, int);
	len = flags->precision > ft_nbrlen(nb) ? flags->precision : ft_nbrlen(nb);
	if (nb < 0)
		flags->padding--;
	if (flags->precision == 0 && nb == 0)
	{
		i += ft_putnchar(' ', flags->padding);
		return (i);
	}
	if (flags->padding > len)
		i += ft_putnchar(' ', flags->padding - len);
	if (nb < 0)
	{
		i++;
		ft_putchar('-');
	}
	if (flags->precision > ft_nbrlen(nb))
		i += ft_putnchar('0', flags->precision - ft_nbrlen(nb));
	ft_putnbr(nb);
	return (i + ft_nbrlen(nb));
}
int put_x(t_flags *flags, va_list param)
{
	int i;
	unsigned int nb;
	int len;

	i = 0;
	nb = (unsigned int)va_arg(param, unsigned int);
	len = flags->precision > ft_hexlen(nb) ? flags->precision : ft_hexlen(nb);
	if (flags->precision == 0 && nb == 0)
	{
		i += ft_putnchar(' ', flags->padding);
		return (i);
	}
	if (flags->padding > len)
		i += ft_putnchar(' ', flags->padding - len);
	if (flags->precision > ft_hexlen(nb))
		i += ft_putnchar('0', flags->precision - ft_hexlen(nb));
	ft_putnbrbase(nb, "0123456789abcdef");
	return (i + ft_hexlen(nb));
}
int put_s(t_flags *flags, va_list param)
{
	int i;
	int j;
	int len;
	char *str;

	i = 0;
	str = (char *)va_arg(param, char *);
	if (!str)
		str = "(null)";
	len = flags->precision < ft_strlen(str) ? flags->precision : ft_strlen(str);
	if (flags->padding > len)
		i += ft_putnchar(' ', flags->padding - len);
	j = 0;
	while (j < len)
	{
		ft_putchar(str[j]);
		j++;
	}
	return (i + j);
	
}
int print_arg(t_flags *flags, const char *str, va_list param)
{
	int i;

	i = 0;
	if (*str == 's')
		i += put_s(flags, param);
	else if (*str == 'd')
		i += put_d(flags, param);
	else if (*str == 'x')
		i += put_x(flags, param);
	return (i);
}
int ft_printf(const char *str, ...)
{
	int i;
	int pchar;
	va_list param;
	t_flags *flags;
	
	i = 0;
	pchar = 0;
	if (!(flags = malloc(sizeof(t_flags))))
		return (-1);
	va_start(param, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i += ft_flags(flags, &(str[i]));
			pchar += print_arg(flags, &(str[i]), param);
		}
		else
		{
			pchar++;
			ft_putchar(str[i]);
		}
		i++;
	}
	va_end(param);
	free(flags);
	return (pchar);
}

