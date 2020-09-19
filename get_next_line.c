#include "get_next_line.h"

int ft_strlen(char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;
	return(len);
}

char *ft_strdub(char *str)
{
	int i = 0;
	char *line = malloc(sizeof(char) * (ft_strlen(str) + 1));

	while (i < ft_strlen(str))
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return(line);
}

int get_next_line(int fd, char **line)
{
	char buff[10000];
	char c = 0;
	int i = 0;

	while (read(fd, &c, 1))
	{
		buff[i] = c;
		if (c == '\n' || c == '\0')
		{
			buff[i] = '\0';
			*line = ft_strdub(buff);
			return(1);
		}
		i++;
	}
	buff[i] = '\0';
	*line = ft_strdub(buff);
	return(0);
}