#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;

	n = 0;
	if (size == 0)
		return (0);
	while (n < size - 1 && src[n])
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	return (1);
}
char	*ft_substr(char const *s, unsigned int start, size_t len, int size)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (len <= size)
		sub = (char *)malloc(len + 1);
	else
		sub = (char *)malloc(size + 1);
	if (!sub || !s)
		return (NULL);
	else
		sub[0] = '\0';
	if (start > (unsigned int)i)
		return (sub);
	i = 0;
	while (len-- && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char const *s1, char const *s2,int s)
{
	int		size1;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	size1 = (int)ft_strlen(s1);
	size1++;
	res =malloc(size1 + s);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, size1);
	ft_strlcpy((res + size1 - 1), s2, s + 1);
	return (res);
}

int ft_strchr(const char *str,int a)
{
	while(a + 1)
	{
		if(str[a] == '\n')
			return (1);
		a--;
	}
	return (0);
}

char *get_next_line(int fd)
{
	char* line;
	char *res;
	int size = 2;
	char *buf;
	char *temp;
	char *temp1;
	int i = 0;

	line = calloc(1,1);
	temp = line;
	buf = malloc(size);
	fd = open("smos",O_RDONLY);
	i = read(fd,buf,size);
	while (!ft_strchr(buf,(size - 1)) && i != 0)
	{
		temp = line;
		line = ft_strjoin(line,buf,size);
		free(temp);
		read(fd,buf,size);
	}
	i = 0;
	while (buf[i++] != '\n');
	temp1 = ft_substr(buf,0,i,size);
	free(buf);
	temp = line;
	line = ft_strjoin(line,temp1,size);
	free(temp1);
	free(temp);
	return line;
}

int main()
{
	char *line;
	int fd;
	fd = open("smos",O_RDONLY);
	line = get_next_line(fd);
	printf("line == %s",line);
	free(line);

	return 0;
}