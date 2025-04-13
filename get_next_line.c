/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:23:48 by djanardh          #+#    #+#             */
/*   Updated: 2025/04/11 15:15:59 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ssize_t read(int fildes, void *buf, size_t nbyte)

/* Function 1: Check if there's a newline and join strings */
static char	*check_and_join(char *stash, int fd)
{
	char	*buffer;
	int		chars_read;
	int		i;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	chars_read = 1;
	while (chars_read > 0)
	{
		i = 0;
		while (stash && stash[i])
		{
			if (stash[i++] == '\n')
				break ;
		}
		if (stash && stash[i - 1] == '\n')
			break ;
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
			break ;
		buffer[chars_read] = '\0';
		stash = ft_strjoin_free(stash, buffer);
	}
	free(buffer);
	return (stash);
}

/* Function 2: Extract line from stash */
static char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

/* Function 3: Create new stash after extracting line */
static char	*create_new_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	len = 0;
	while (stash[i + len])
		len++;
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i + j])
	{
		new_stash[j] = stash[i + j];
		j++;
	}
	new_stash[j] = '\0';
	return (new_stash);
}

/* Function 4: Join strings and free first string */
// static char	*ft_strjoin_free(char *s1, char *s2)
// {
// 	char	*result;
// 	int		i;
// 	int		j;
// 	int		len1;
// 	int		len2;

// 	len1 = 0;
// 	while (s1 && s1[len1])
// 		len1++;
// 	len2 = 0;
// 	while (s2 && s2[len2])
// 		len2++;
// 	result = malloc(len1 + len2 + 1);
// 	if (!result)
// 		return (NULL);
// 	i = -1;
// 	while (s1 && ++i < len1)
// 		result[i] = s1[i];
// 	j = -1;
// 	while (s2 && ++j < len2)
// 		result[i + j] = s2[j];
// 	result[i + j] = '\0';
// 	if (s1)
// 		free(s1);
// 	return (result);
// }

/* Function 5: Main get_next_line function */
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = check_and_join(stash, fd);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	temp = create_new_stash(stash);
	free(stash);
	stash = temp;
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*result;
// 	int		count;

// 	count = 0;
// 	fd = open("test.txt", O_RDWR);
// 	if (fd < 0)
// 	{
// 		printf("error opening file");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		result = get_next_line(fd);
// 		if (result == NULL)
// 			break ;
// 		count++;
// 		printf("[%d]: %s\n", count, result);
// 		free(result);
// 		result = NULL;
// 	}
// 	close(fd);
// 	return (0);
// }
