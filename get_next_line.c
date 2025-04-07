/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:23:48 by djanardh          #+#    #+#             */
/*   Updated: 2025/04/07 20:14:43 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ssize_t read(int fildes, void *buf, size_t nbyte)

char	*get_next_line(int fd)
{
	char		*buf;
	int			chars_read;
	char		*new_line_position;
	static char	*stash;
	char		*temp_str;
	static int	flag;

	flag = 0;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	temp_str = "";
	if (flag == 1)
	{
		free(stash);
		flag = 0;
	}
	if (!buf)
		return (NULL);
	chars_read = read(fd, buf, BUFFER_SIZE);
	buf[chars_read] = '\0';
	stash = ft_strdup(buf);
	if (!stash)
		return (NULL);
	new_line_position = ft_strchr(stash, '\n');
	temp_str = ft_strjoin(temp_str, stash);
	while (!new_line_position)
	{
		temp_str = ft_strjoin(temp_str, stash);
	}
	if (new_line_position)
	{
		*temp_str = '\0';
		flag = 1;
		return (temp_str);
	}
	if (chars_read <= 0)
		return (free(buf), NULL);
	return (temp_str);
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
