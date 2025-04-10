/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:23:48 by djanardh          #+#    #+#             */
/*   Updated: 2025/04/10 15:49:32 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ssize_t read(int fildes, void *buf, size_t nbyte)

static int	newline_position(char *s)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i);
	return (-1);
}

static void	update_stash(char **stash, int i)
{
	int		j;
	char	*temp;
	size_t	stash_len;

	j = 0;
	if (!(*stash)[i + 1])
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	stash_len = ft_strlen(*stash);
	temp = malloc((stash_len - i) * sizeof(char));
	if (!temp)
		return ;
	i++;
	while ((*stash)[i])
		temp[j++] = (*stash)[i++];
	temp[j] = '\0';
	free(*stash);
	*stash = temp;
}

static char	*extract_line(char **stash)
{
	int		i;
	char	*line;
	int		nl_pos;

	i = 0;
	nl_pos = newline_position(*stash);
	if (nl_pos == -1)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	line = malloc(nl_pos + 2);
	if (!line)
		return (NULL);
	while (i <= nl_pos)
	{
		line[i] = (*stash)[i];
		i++;
	}
	line[i] = '\0';
	update_stash(stash, nl_pos);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			chars_read;
	static char	*stash;

	stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	chars_read = 1;
	while (chars_read > 0)
	{
		if (stash && ft_strchr(stash, '\n'))
			break ;
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (chars_read <= 0)
			break ;
		buf[chars_read] = '\0';
		if (!stash)
			stash = ft_strdup(buf);
		else
			stash = ft_strjoin_free(stash, buf);
		if (!stash)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	if (!stash)
		return (NULL);
	if (chars_read <= 0 && !ft_strlen(stash))
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (extract_line(&stash));
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
