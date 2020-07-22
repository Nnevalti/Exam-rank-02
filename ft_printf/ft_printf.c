#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct		s_flags
{
	int		padding;
	int		precision;
}					t_flags;

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

int			ft_strchr(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);

}

int			ft_atoi(const char *str)
{
	int		i;
	int		value;

	i = 0;
	value = 0;
	while (ft_isdigit(str[i]))
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	return (value);
}

int			ft_putnstr(char c, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

void	init_flags(t_flags *flags)
{
	flags->padding = 0;
	flags->precision = -1;
}

int			ft_width(t_flags *flags, const char *str)
{
	int		i;

	i = 0;
	flags->padding = ft_atoi(str);
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

int			ft_precision(t_flags *flags, const char *str)
{
	int		i;

	i = 0;
	flags->precision = ft_atoi(str);
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

int			ft_flags(t_flags *flags, const char *str)
{
	int		i;

	i = 1;
	init_flags(flags);
	while (ft_strchr("0123456789.", str[i]))
	{
		if (ft_isdigit(str[i]))
		{
			i += ft_width(flags, &(str[i]));
		}
		else if (str[i] == '.')
		{
			i++;
			i+= ft_precision(flags, &(str[i]));
		}
	}
	return (i);

}

int			ft_nbrlen(int nb)
{
	int		i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int			ft_hexlen(unsigned int nb)
{
	int		i;

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
		ft_putchar((n % 10) + '0');
}

void ft_putnbrbase(unsigned int nb, char *base)
{
	if (nb < 0)
		nb = -nb;
	if (nb >= 16)
	{
		ft_putnbrbase(nb / 16, base);
		ft_putnbrbase(nb % 16, base);
	}
	else
		ft_putchar(base[nb % 16]);
}

int				put_s(t_flags *flags, va_list param)
{
	int			i;
	int			j;
	int			len;
	char		*str;

	i = 0;
	str = (char *)va_arg(param, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags->precision >= 0 && flags->precision < len)
		len = flags->precision;
	i += ft_putnstr(' ', flags->padding - len);
	j = 0;
	while (j < len)
	{
		ft_putchar(str[j]);
		j++;
	}
	return (i + j);
}

int			put_d(t_flags *flags, va_list param)
{
	int		i;
	int		nb;
	int		len;

	i = 0;
	nb = (int)va_arg(param, int);
	if (nb < 0)
		flags->padding--;
	len = flags->precision > ft_nbrlen(nb) ? flags->precision : ft_nbrlen(nb);
	if (flags->precision == 0 && nb == 0)
	{
		i += ft_putnstr(' ', flags->padding);
		return (i);
	}
	if (flags->padding > len)
		i += ft_putnstr(' ', flags->padding - len);
	if (nb < 0)
	{
		ft_putchar('-');
		i++;
	}
	if (flags->precision > ft_nbrlen(nb))
		i += ft_putnstr('0', flags->precision - ft_nbrlen(nb));
	ft_putnbr(nb);
	return (i + ft_nbrlen(nb));
}

int			put_x(t_flags *flags, va_list param)
{
		unsigned int nb;
		int len;
		int i;

		i = 0;
		nb = (unsigned int)va_arg(param, unsigned int);
		len = flags->precision > ft_hexlen(nb) ? flags->precision : ft_hexlen(nb);
		if (flags->precision == 0 && nb == 0)
		{
			i += ft_putnstr(' ', flags->padding);
			return (i);
		}
		if (flags->padding > len)
			i += ft_putnstr(' ', flags->padding - len);
		if (flags->precision > ft_hexlen(nb))
			i += ft_putnstr('0', flags->precision - ft_hexlen(nb));
		ft_putnbrbase(nb, "0123456789abcdef");
		return (i + ft_hexlen(nb));
}

int			print_arg(const char *str, t_flags *flags, va_list param)
{
	int		i;

	i = 0;
	if(*str== 's')
		i += put_s(flags, param);
	else if (*str =='d')
		i += put_d(flags, param);
	else if (*str == 'x')
		i += put_x(flags, param);
	return (i);
}

int			ft_printf(const char *str, ... )
{
	va_list	param;
	t_flags	*flags;
	int		i;
	int		pchar;

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
			pchar += print_arg(&(str[i]), flags, param);
		}
		else
		{
			ft_putchar(str[i]);
			pchar++;
		}
		i++;
	}
	free(flags);
	va_end(param);
	return (pchar);
}
