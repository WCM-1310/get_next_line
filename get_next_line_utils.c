/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warcharo <warcharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:38:04 by warcharo          #+#    #+#             */
/*   Updated: 2024/11/07 23:33:05 by warcharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str)
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*new;
	char	*ptr;

	new = (char *)malloc(ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	ptr = new;
	while (*str)
		*ptr++ = *str++;
	*ptr = '\0';
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	char	*ptr;

	new = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ptr = new;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '/0';
	return (new);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substring;
	int		i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substring = (char *) malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	substring[i] = '/0';
	return (substring);
}
