#include <stdio.h>
#include <stdlib.h>

int               get_next_line(char **line);

int    main(int ac, char **av)
{
  char *line;

  while (get_next_line(&line) > 0)
  {
    printf("Line : %s\n", line);
    free(line);
  }
  printf("%s\n", line);
  free(line);
  line = NULL;
  return (0);
}
