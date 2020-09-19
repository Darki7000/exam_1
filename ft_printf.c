#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
//////////////////
#include <stdio.h>

int p_res;
int p_dot;
int p_wd;

void ft_putchar(char c)
{
	write(1, &c, 1);
	p_res += 1;
}

void ft_putstr(char *str, int len)
{
	while (len > 0)
	{
		ft_putchar(*str);
		str++;
		len--;
	}
}

int ft_strlen(char *str)
{
	int len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char *ft_itoa(unsigned long nb, int base)
{
	char *str = NULL;
	int len = 0;
	unsigned long tmp = nb;

	if (tmp == 0)
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
		str[len - 1] = nb % base;
		if ((nb % base) > 9)
			str[len - 1] += 'a' - 10;
		else
			str[len - 1] += '0';
		nb /= base;
		len--;
	}
	return (str);
}

void ft_print_s(char *str)
{
	int len = ft_strlen(str);
	if (p_dot != -1 && len > p_dot)
		len = p_dot;
	while (p_wd > len)
	{
		ft_putchar(' ');
		p_wd--;
	}
	ft_putstr(str, len);
}

void ft_print_x(unsigned int x)
{
	char *str = ft_itoa(x, 16);
	int len = ft_strlen(str);
	if (p_dot != -1 && len < p_dot)
		len = p_dot;
	while (p_wd > len)
	{
		ft_putchar(' ');
		p_wd--;
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
	if (p_dot != -1 && len < p_dot)
		len = p_dot;
	while (p_wd > (len + min))
	{
		ft_putchar(' ');
		p_wd--;
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

int ft_printf(const char *str, ... )
{
	va_list ap;
	int i = 0;

	p_res = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i+1] != '\0')
		{
			p_wd = 0;
			p_dot = -1;
			i++;
			while (str[i] >= '0' && str[i] <= '9')
			{
				p_wd = p_wd * 10 + (str[i] - '0');
				i++;
			}
			if (str[i] == '.')
			{
				i++;
				p_dot = 0;
				while (str[i] >= '0' && str[i] <= '9')
				{
					p_dot = p_dot * 10 + (str[i] - '0');
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
	return (p_res);
}



int main()
{
	int i, i1;
	i = ft_printf("%s\n", "toto");
	i1 = printf("%s\n", "toto");
	printf("my: %i test: %i\n\n", i, i1);
	i = ft_printf("Magic %s is %5.3d\n", "number", -42);
	i1 = printf("Magic %s is %5.3d\n", "number", -42);
	printf("my: %i test: %i\n\n", i, i1);
	i = ft_printf("Hexadecimal for is %10.8x\n", -42);
	i1 = printf("Hexadecimal for is %10.8x\n", -42);
	printf("my: %i test: %i\n\n", i, i1);
}