/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:23:48 by djanardh          #+#    #+#             */
/*   Updated: 2025/04/05 17:14:23 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ssize_t read(int fildes, void *buf, size_t nbyte)

static size_t	ft_strlen(char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (src[count] != '\0')
		count++;
	if (dstsize > 0)
	{
		while ((src[i] != '\0') && (i < (dstsize - 1)))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (count);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while ((src[i] != '\0' && (dst_len + i < dstsize - 1)))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// The strduplication() function allocates sufficient memory for a copy of the
// string s1, does the copy, and returns a pointer to it.  The pointer may
// subsequently be used as an argument to the function free(3).
// If insufficient memory is available, NULL is returned and errno is set to
// ENOMEM.
static char	*ft_strdup(char *s1)
{
	char	*s2;
	size_t	str_len;
	int		i;

	i = 0;
	str_len = ft_strlen(s1);
	s2 = malloc(str_len + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return ((char *)s2);
}

static int	ft_putstr(char *s)
{
	size_t	s_len;

	if (s == NULL)
		return (write(1, "(null)", 6));
	s_len = ft_strlen(s);
	return (write(1, s, s_len));
}

// s1: The prefix string.
// s2: The suffix string.
// Return value: The new string. NULL if the allocation fails.
// Description:
// Allocates memory (using malloc(3)) and returns a new string,
// which is the result of concatening ’s1’ and ’s2’
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_string;
	size_t	newstr_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr_len = s1_len + s2_len + 1;
	new_string = malloc(newstr_len);
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s1, newstr_len);
	ft_strlcat(new_string, s2, newstr_len);
	new_string[newstr_len - 1] = '\0';
	return (new_string);
}

char	*ft_strchr(char *s, int c)
{
	char			a;
	unsigned int	i;
	size_t			s_len;

	a = (char)c;
	i = 0;
	s_len = ft_strlen(s);
	if (a == '\0')
		return ((char *)&s[s_len]);
	while (s[i] != '\0')
	{
		if (s[i] == a)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

static size_t	ft_malloc_size(size_t s_len, size_t start, size_t len)
{
	size_t	remaining_len;
	size_t	malloc_size;

	remaining_len = s_len - start;
	if (len < remaining_len)
		malloc_size = len;
	else
		malloc_size = remaining_len;
	return (malloc_size);
}

// s: The original string from which to create the substring.
// start: The starting index of the substring within ’s’.
// len: The maximum length of the substring.
// Allocates memory (using malloc(3)) and returns a substring from the string
// ’s’. The substring starts at index ’start’ and has a maximum length of ’len’
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub_string;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	sub_string = malloc(ft_malloc_size(s_len, start, len) + 1);
	if (sub_string == NULL)
		return (NULL);
	while (s[start] != '\0' && (i < len) && start < s_len)
	{
		sub_string[i] = s[start];
		i++;
		start++;
	}
	sub_string[i] = '\0';
	return (sub_string);
}

char	*new_line_check(char *stash, int chars_read, char *storage)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (i < (chars_read))
	{
		if (stash[i] == '\n' && flag == 0)
		{
			stash[i + 1] = '\0';
			return (stash);
		}
		i++;
	}
	if (i = chars_read)
	{
		storage = ft_strjoin(storage, stash);
		flag = 1;
	}
}

char	*get_next_line(int fd)
{
	static char	*buf;
	int			chars_read;
	char		*stash;
	int			i;
	char		**result;
	static int	count;
	char		*storage;

	count = 0;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while ((chars_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[chars_read] = '\0';
		stash = ft_strdup(buf); // here stash is malloc'd,should this be freed ?
	}
	if (chars_read == 0)
		return (???);
	result[count] = new_line_check(stash, chars_read);
	free(stash);
}
return (stash);
}

#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*result;

	fd = open("test.txt", O_RDWR);
	result = get_next_line(fd);
	printf("%s", result);
	close(fd);
	return (0);
}
