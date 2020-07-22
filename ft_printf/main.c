#include <stdio.h>

int ft_printf(const char *, ... );

int		main(void)
{
	int ret;
	int	ret2;

	ft_printf("padding : 10, precision : 2, str : toto\n");
	ret = printf("-%10.2s-\n", "toto");
	ret2 = ft_printf("-%10.2s-\n", "toto");
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 10, precision : 5, str : toto\n");
	ret = printf("-%10.5s-\n", "toto");
	ret2 = ft_printf("-%10.5s-\n", "toto");
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("precision : 0, str : toto\n");
	ret = printf("-%.0s-\n", "toto");
	ret2 = ft_printf("-%.0s-\n", "toto");
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 0, precision : 4, str : NULL\n");
	ret = printf("-%0.4s-\n", NULL);
	ret2 = ft_printf("-%0.4s-\n", NULL);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	printf("NBR\n");
	ft_printf("padding : 10, precision : none, nb : 42\n");
	ret = printf("-%10d-\n", 42);
	ret2 = ft_printf("-%10d-\n", 42);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 10, precision : 12, nb : -42\n");
	ret = printf("-%10.12d-\n", -42);
	ret2 = ft_printf("-%10.12d-\n", -42);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 10, precision : 0, nb : 0\n");
	ret = printf("-%10.0d-\n", 0);
	ret2 = ft_printf("-%10.0d-\n", 0);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 10, precision : 5, nb : 42\n");
	ret = printf("-%10.5d-\n", 42);
	ret2 = ft_printf("-%10.5d-\n", 42);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 10, precision : 10, nb : -42\n");
	ret = printf("-%10.10d-\n", -42);
	ret2 = ft_printf("-%10.10d-\n", -42);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 1, precision : none, nb : -42\n");
	ret = printf("-%1d-\n", -42);
	ret2 = ft_printf("-%1d-\n", -42);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 1, precision : none, nb : -42\n");

	printf("HEX\n");
	ft_printf("padding : 10, precision : 0, nb : 0\n");
	ret = printf("-%10.0x-\n", 0);
	ret2 = ft_printf("-%10.0x-\n", 0);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 10, precision : none, nb : 42\n");
	ret = printf("-%10x-\n", 42);
	ret2 = ft_printf("-%10x-\n", 42);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);

	ft_printf("padding : 10, precision : none, nb : -42\n");
	ret = printf("-%10x-\n", -42);
	ret2 = ft_printf("-%10x-\n", -42);
	printf("printf, ft_printf : %d, %d\n", ret, ret2);
	return (0);
}
