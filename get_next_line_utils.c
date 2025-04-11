/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:23:58 by djanardh          #+#    #+#             */
/*   Updated: 2025/04/11 16:49:20 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*ft_strchr(char *s, int c)
{
	char	a;
	size_t	i;
	size_t	s_len;

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

char	*ft_strdup(char *s1)
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_string;
	size_t	newstr_len;

	if (s1)
		s1_len = ft_strlen(s1);
	else
		s1_len = 0;
	s2_len = ft_strlen(s2);
	newstr_len = s1_len + s2_len + 1;
	new_string = malloc(newstr_len);
	if (new_string == NULL)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	if (s1)
		ft_strlcpy(new_string, s1, s1_len + 1);
	else
		new_string[0] = '\0';
	ft_strlcat(new_string, s2, newstr_len);
	if (s1)
		free(s1);
	return (new_string);
}

// static char	*ft_strjoin_free(char *s1, char *s2)
// {
// 	char	*result;
// 	int		i;
// 	int		j;
// 	size_t	len1;
// 	size_t	len2;

// 	len1 = ft_strlen_safe(s1);
// 	len2 = ft_strlen_safe(s2);
// 	result = malloc(len1 + len2 + 1);
// 	if (!result)
// 	{
// 		if (s1)
// 			free(s1);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (s1 && s1[i])
// 	{
// 		result[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2 && s2[j])
// 		result[i++] = s2[j++];
// 	result[i] = '\0';
// 	if (s1)
// 		free(s1);
// 	return (result);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	size_t s1_len;
// 	size_t s2_len;
// 	char *new_string;
// 	size_t newstr_len;

// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	newstr_len = s1_len + s2_len + 1;
// 	new_string = malloc(newstr_len);
// 	if (new_string == NULL)
// 		return (NULL);
// 	ft_strlcpy(new_string, s1, newstr_len);
// 	ft_strlcat(new_string, s2, newstr_len);
// 	new_string[newstr_len - 1] = '\0';
// 	return (new_string);
// }