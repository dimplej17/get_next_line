/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:23:48 by djanardh          #+#    #+#             */
/*   Updated: 2025/04/08 19:40:39 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ssize_t read(int fildes, void *buf, size_t nbyte)

static int	newline_position(char *s, int c)
{
	char	a;
	size_t	i;

	a = (char)c;
	i = 0;
	while (s[i] != '\n')
		i++;
	return (i);
}

static void	update_stash(char **stash, int i)
{
	int		j;
	char	*temp;
	size_t	stash_len;

	stash_len = ft_strlen(*stash);
	j = 0;
	temp = malloc(stash_len - newline_position(*stash, '\n'));
	if (!temp)
		return ;
	while (*stash[i] != '\0')
	{
		temp[j] = *stash[i + 1];
		j++;
		i++;
	}
	*stash = temp;
}

static char	*processing_line(char *stash)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = malloc((newline_position(stash, '\n') + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	while (stash[i] != '\n')
	{
		new_line[i] = stash[i];
		i++;
	}
	new_line[i] = '\n';
	new_line[i + 1] = '\0';
	update_stash(&stash, i);
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			chars_read;
	static char	*stash;

	chars_read = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (free(buf), NULL);
	if (!stash)
		stash = ft_strdup("");
	while (!(ft_strchr(buf, '\n')) && chars_read > 0)
	{
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (chars_read <= 0)
			return (free(buf), NULL);
		buf[chars_read] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	if (ft_strchr(stash, '\n'))
		return (free(buf), processing_line(stash));
	if (chars_read <= 0)
		return (stash);
	return (stash);
}

int	main(void)
{
	int		fd;
	char	*result;
	int		count;

	count = 0;
	fd = open("test.txt", O_RDWR);
	if (fd < 0)
	{
		printf("error opening file");
		return (1);
	}
	while (1)
	{
		result = get_next_line(fd);
		if (result == NULL)
			break ;
		count++;
		printf("[%d]: %s\n", count, result);
		free(result);
		result = NULL;
	}
	close(fd);
	return (0);
}
