#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int dot;
int wd;
int res;

int ft_strlen(char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;
	return(len);
}

char *ft_strdub(char *str)
{
	char *line = malloc(sizeof(char) * (ft_strlen(str) + 1));
	int i = 0;

	while (str[i])
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return(line);
}

int get_next_line(char **line)
{
	char buff[10000];
	char c = 0;
	int i = 0;

	while (read(0, &c, 1))
	{
		if (c == '\n' || c == '\0')
		{
			buff[i] = '\0';
			*line = ft_strdub(buff);
			return(1);
		}
		buff[i] = c;
		i++;
	}
	buff[i] = '\0';
	*line = ft_strdub(buff);
	return(0);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
	res++;
}

void ft_putstr(char *str, int len)
{
	int i = 0;

	while (i < len)
	{
		ft_putchar(str[i]);
		i++;
	}
}

void ft_print_s(char *str)
{
	int len = ft_strlen(str);

	if (dot < len && dot != -1)
		len = dot;
	while (wd > len)
	{
		ft_putchar(' ');
		wd--;
	}
	ft_putstr(str, len);
}

char *ft_itoa(unsigned int nb, int base)
{
	int len = 0;
	unsigned int tmp = nb;
	char *str;

	if (nb == 0)
		len++;
	while (tmp > 0)
	{
		tmp /= base;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len > 0)
	{
		str[len-1] = nb % base;
		if ((nb % base) > 9)
			str[len-1] += 'a' - 10;
		else
			str[len-1] += '0';
		len--;
		nb /= base;
	}
	return (str);
}

void ft_print_x(unsigned long x)
{
	char *str = ft_itoa(x, 16);
	int len = ft_strlen(str);

	if (dot > len && dot != -1)
		len = dot;
	while (wd > len)
	{
		ft_putchar(' ');
		wd--;
	}
	while (len > ft_strlen(str))
	{
		ft_putchar('0');
		len--;
	}
	ft_putstr(str, len);
}

void ft_print_d(long d)
{
	int min = 0;
	if (d < 0)
	{
		min = 1;
		d *= -1;
	}
	char *str = ft_itoa(d, 10);
	int len = ft_strlen(str);

	if (dot > len && dot != -1)
		len = dot;
	while (wd > (len + min))
	{
		ft_putchar(' ');
		wd--;
	}
	if (min == 1)
		ft_putchar('-');
	while (len > ft_strlen(str))
	{
		ft_putchar('0');
		len--;
	}
	ft_putstr(str, len);
}

#include <stdio.h>

int ft_printf(const char *str, ... )
{
	va_list ap;
	int i = 0;

	va_start(ap, str);
	res = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i+1])
		{
			wd = 0;
			dot = -1;
			i++;
			while (str[i] >= '0' && str[i] <= '9')
			{
				wd = wd * 10 + (str[i] - '0');
				i++;
			}
			if (str[i] == '.')
			{
				dot = 0;
				i++;
				while (str[i] >= '0' && str[i] <= '9')
				{
					dot = dot * 10 + (str[i] - '0');
					i++;
				}
			}
			
			if (str[i] == 's')
				ft_print_s(va_arg(ap, char *));
			else if (str[i] == 'x')
				ft_print_x(va_arg(ap, unsigned int));
			else if (str[i] == 'd')
				ft_print_d(va_arg(ap, int));
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return(res);
}



int main()
{
	int i = 0, i1 = 0;
	i = ft_printf("%10.s\n", "toto");
	i1 = printf("%10.s\n", "toto");
	printf("my: %i test: %i\n\n", i, i1);
	i = ft_printf("Magic %s is %5.d\n", "number", 42);
	i1 = printf("Magic %s is %5.d\n", "number", 42);
	printf("my: %i test: %i\n\n", i, i1);
	i = ft_printf("Hexadecimal for is %10.8x\n", -42);
	i1 = printf("Hexadecimal for is %10.8x\n", -42);
	printf("my: %i test: %i\n\n", i, i1);
}