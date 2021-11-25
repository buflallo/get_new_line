#include "get_next_test.h"


int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)(s);
	while (i < n)
	{
		temp[i] = '\0';
		i++;
	}
}

int	ft_strchr(char *a, char b)
{
	int	i;

	if (!a)
		return (-1);
	i = 0;
	while (a[i])
	{
		if (a[i] == b)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	else
		sub[0] = '\0';
	i = 0;
	while (len-- && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char *a, char *b)
{
	int		i;
	int		j;
	char	*rend;

	i = 0;
	j = 0;
	rend = malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) + 1));
	if (!rend)
		return (NULL);
	while (a && a[i])
	{
		rend[i] = a[i];
		i++;
	}
	while (b && b[j])
	{
		rend[i + j] = b[j];
		j++;
	}
	rend[i + j] = '\0';
	return (rend);
}

char	*get_next_line(int fd)
{
	char *buf;
	static char *stock;
	int t,l = 1;
	int x = 10;
	char *line;
	char *temp;

	t = ft_strchr(stock,'\n');
	temp = NULL;
	if (t == -1)
	{
		buf = malloc(x + 1);
		ft_bzero(buf, x + 1);
		while (t == -1 && l != 0)
		{
			l = read(fd, buf, x);
			if (l)
			{
				if(stock)
					temp = stock;
				stock = ft_strjoin(stock, buf);
				if(temp)
				{
					free(temp);
					temp = NULL;
				}
			}
			t = ft_strchr(stock,'\n');
		}
		free(buf);
	}
	if (!stock)
		return NULL;
	if (l == 0)
	{
		line = stock;
		stock = NULL;
		return line;
	}
	line = ft_substr(stock, 0, t + 1);
	temp = stock;
	stock = ft_substr(stock, t+1, ft_strlen(stock));
	free(temp);
	return line;
}

int	main(void)
{
	int	fd;
	char *line;
	int	i;

	i = 0;
	fd = open("smos", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s",line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}