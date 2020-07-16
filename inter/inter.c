#include <unistd.h>

int			not_used(char c, char *str, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		if (str[j] == c)
			return (0);
		j++;
	}
	return (1);
}

void		ft_inter(char *str1, char *str2)
{
	int		i;
	int		j;

	i = 0;
	while (str1[i])
	{
		j = 0;
		while (str2[j])
		{
			if (str1[i] == str2[j] && not_used(str1[i], str1, i)
			&& not_used(str1[i], str2, j))
				write(1, &str1[i], 1);
			j++;
		}
		i++;
	}
}

int			main(int ac, char **av)
{
	if (ac == 3)
	{
		ft_inter(av[1], av[2]);
	}
	write(1, "\n", 1);
	return (0);
}
