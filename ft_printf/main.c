#include <stdio.h>

int ft_printf(const char *, ... );

int		main(void)
{
	ft_printf("padding : 10, precision : 2, str : toto\n");
	ft_printf("-%10.2s-\n", "toto");
	printf("-%10.2s-\n", "toto");

	ft_printf("padding : 10, precision : 5, str : toto\n");
	ft_printf("-%10.5s-\n", "toto");
	printf("-%10.5s-\n", "toto");

	ft_printf("precision : 0, str : toto\n");
	ft_printf("-%.0s-\n", "toto");
	printf("-%.0s-\n", "toto");

	ft_printf("padding : 0, precision : 4, str : NULL\n");
	ft_printf("-%0.4s-\n", NULL);
	printf("-%0.4s-\n", NULL);

	// printf("NBR\n");
	// printf("%10d\n", 42);
	// printf("%10d\n", -42);
	// printf("%10x\n", 42);
	// printf("%10x\n", -42);
	return (0);
}
