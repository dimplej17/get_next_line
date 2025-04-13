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

/* Function 1: Check for newline in string */
static int  has_newline(char *s)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
    {
        if (s[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

/* Function 2: Read from file and build stash */
static char *read_file(int fd, char *stash)
{
    char    *buf;
    int     chars_read;

    buf = malloc(BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);
    chars_read = 1;
    while (!has_newline(stash) && chars_read > 0)
    {
        chars_read = read(fd, buf, BUFFER_SIZE);
        if (chars_read < 0)
        {
            free(buf);
            if (stash)
                free(stash);
            return (NULL);
        }
        buf[chars_read] = '\0';
        stash = ft_strjoin_free(stash, buf);
    }
    free(buf);
    return (stash);
}

/* Function 3: Get line from stash */
static char *get_line(char *stash)
{
    char    *line;
    int     i;
    int     j;

    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')	
        line = malloc(i + 2);
    else
        line = malloc(i + 1);
    if (!line)
        return (NULL);
    j = 0;
    while (j < i)
    {
        line[j] = stash[j];
        j++;
    }
    if (stash[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return (line);
}

/* Function 4: Update stash after extracting line */
static char *update_stash(char *stash)
{
    char    *new_stash;
    int     i;
    int     j;

    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++;
    if (!stash[i])
        return (free(stash), NULL);
    new_stash = malloc(ft_strlen(stash) - i + 1);
    if (!new_stash)
    {
        free(stash);
        return (NULL);
    }
    j = 0;
    while (stash[i])
        new_stash[j++] = stash[i++];
    new_stash[j] = '\0';
    free(stash);
    return (new_stash);
}

/* Function 5: Main get_next_line function */
char    *get_next_line(int fd)
{
    static char *stash;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
    {
        if (stash)
            free(stash);
        stash = NULL;
        return (NULL);
    }
    stash = read_file(fd, stash);
    if (!stash || !(*stash))
    {
        free(stash);
        stash = NULL;
        return (NULL);
    }
    line = get_line(stash);
    stash = update_stash(stash);
    return (line);
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
