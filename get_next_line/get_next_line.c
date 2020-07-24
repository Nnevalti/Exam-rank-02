#include <unistd.h>
#include <stdlib.h>

int   ft_strlen(char *str)
{
  int   i;

  i = 0;
  while(str[i])
    i++;
  return (i);
}

char    *ft_strjoin(char *str1, char *str2)
{
  int   i;
  int   j;
  char  *res;

  if(!(res = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1))))
    return (0);
  while (str1[i])
  {
    res[i] = str1[i];
    i++;
  }
  while (str2[j])
  {
    res[i + j] = str2[j];
    j++;
  }
  res[i + j] = '\0';
  return (res);
}

char    *ft_substr(char *str, int start, int len)
{
    int     i;
    char    *res;

    i = 0;
    if (!(res = malloc(sizeof(char) * len + 1)))
      return (0);
    while (len-- && str[start + i])
    {
      res[i] = str[start + i];
      i++;
    }
    res[i] = '\0';
    return (res);
}

char *ft_strdup(char *str)
{
  char  *res;
  int   i;

  if (!(res = malloc(sizeof(char) * ft_strlen(str) + 1)))
    return (0);
  i = 0;
  while (str[i])
  {
    res[i] = str[i];
    i++;
  }
  res[i] = '\0';
  return (res);
}

int   ft_strchr(char *str, char c)
{
  int   i;

  i = 0;
  while (str[i])
  {
    if (str[i] == c)
      return (1);
    i++;
  }
  return (0);
}

int               get_next_line(char **line)
{
      int         res;
      static char *str;
      char        *buf;
      char        *tmp;
      int         i;

      if (!(buf = malloc(sizeof(char) * 256)))
        return (-1);
      if (!line)
        return (-1);
      while (res = read(0, buf, 255) > 0)
      {
        buf[res] = '\0';
        if (!str || !*str)
        {
          tmp = ft_strdup(buf);
          free(str);
          str = tmp;
        }
        else
        {
            tmp = ft_strjoin(str, buf);
            free(str);
            str = tmp;
        }
        if (ft_strchr(str, '\n'))
          break ;
      }
      free(buf);
      while (str[i] != '\n' || str[i]  != '\0')
        i++;
      *line = ft_substr(str, 0, i);
      if (str[i] == '\n')
        tmp = ft_strdup(str);
      else
        tmp = NULL;
      free(str);
      str = tmp;
      if (res < 0)
        return (-1);
      if (res == 0 || !str)
        return (0);
      return (1);
}
