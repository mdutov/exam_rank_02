#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_memdel(char	*s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
}

char	*ft_strchr(char *s, int c)
{
	char	*d;

	d = s;
	while (*d)
	{
		if (*d == c)
			return (d);
		d++;
	}
	if (*d == c && c == '\0')
		return (d);
	return (NULL);
}

char	*ft_memmove(char *s1, char *s2, size_t n)
{
	char *d1;
	char *d2;

	d1 = s1;
	d2 = s2;
	if (!d1 && !d2)
		return (NULL);
	if (n != 0)
	{
		if (d1 < d2)
			while (n--)
				*d1++ = *d2++;
		if (d1 > d2)
		{
			d1 = d1 + (n - 1);
			d2 = d2 + (n - 1);
			while (n--)
				*d1-- = *d2--;
		}
	}
	return (d1);
}

void	ft_memset(char *s, int c, size_t n)
{
	char	*d;

	d = s;
	if (n)
	{
		while (n--)
			*d++ = c;
	}
}

char	*ft_newstr(size_t n)
{
	void	*d;

	if (n < 0)
		return(NULL);
	if ((d = malloc(sizeof(char) * (n + 1))))
		ft_memset((char *)d, 0, n);
	*((char *)d + n) = '\0';
	return ((char *)d);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*d1;
	char	*d2;
	char	*bgn;
	char	*tmp;

	d1 = s1;
	d2 = s2;
	if (!d1 && !d2)
		return (NULL);
	bgn = ft_newstr((s1 ? ft_strlen(s1) : 0) + (s2 ? ft_strlen(s2) : 0));
	tmp = bgn;
	if (d1)
		while (*d1)
			*tmp++ = *d1++;
	if (d2)
		while (*d2)
			*tmp++ = *d2++;
	return (bgn);
}

void		next_str_to_buf(char **line, char *buf)
{
	int				len;
	char			*del_ln;

	del_ln = *line;
	*line = ft_strjoin(*line, buf);
	ft_memdel(del_ln);
	len = BUFFER_SIZE - ft_strlen(buf);
	ft_memmove(buf, buf + ft_strlen(buf) + 1, len);
	ft_memset(buf + len, 0, BUFFER_SIZE - len);
}

int		get_next_line(char **line)
{
	static char		buf[BUFFER_SIZE + 1];
	char			*ptr;
	int				rd;

	if (BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = ft_newstr(0);
	rd = 1;
	while (rd)
	{
		if ((ptr = ft_strchr(buf, '\n')))
			*ptr = '\0';
		next_str_to_buf(line, buf);
		if (ptr)
			return (1);
		rd = read(0, buf, BUFFER_SIZE);
	}
	return (rd);
}
