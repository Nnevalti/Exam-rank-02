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

void	init_flags(t_flags *flags)
{
	flags->padding = 0;
	flags->precision = 0;
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
	while (i < flags->padding - len)
	{
		ft_putchar(' ');
		i++;
	}
	j = 0;
	while (j < len)
	{
		ft_putchar(str[j]);
		j++;
	}
	return (i + j);
}

int			ft_nbrlen(int nb, int base)
{
	int		i;

	if (nb == 0)
		return (1);
	else if (base == 10 && nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		nb \= base;
		i++;
	}
	return (i);
}

int			put_d(t_flags *flags, va_list param)
{
	int		i;
	int		nb;
	int		len;

	nb = (int)va_arg(parameters, int);
	len = ft_nbrlen(nb, 10);

}

int			put_x(t_flags *flags, va_list param)
{

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
