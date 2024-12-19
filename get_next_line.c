/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warcharo <warcharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:08:08 by warcharo          #+#    #+#             */
/*   Updated: 2024/12/19 03:16:26 by warcharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	copy_line(t_list *stash, char *string)
{
	int	i;
	int	j;

	i = 0;
	while (stash)
	{
		j = 0;
		while (stash->content[j])
		{
			if (stash->content[j] == '\n')
			{
				string[i++] = '\n';
				string[i] = '\0';
				break ;
			}
			string[i++] = stash->content[j++];
		}
		stash = stash->next;
	}
	string[i] = '\0';
}

// Read from file BUFFER_SIZE characters -> Create a node
// -> Add it to the back of linked list
static void	read_to_buffer(int fd, t_list **stash)
{
	t_list	*read_content;
	char	*buffer;
	int		read_char;

	while (!have_newline(*stash))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		read_char = read(fd, buffer, BUFFER_SIZE);
		if (read_char <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[read_char] = '\0';
		read_content = ft_lstnew(buffer);
		if (!read_content)
			return ;
		ft_lstadd_back(stash, read_content);
	}
}

// Traverse the [buffer] to get one line -> Store it in [line]
// Use have_newline() here instead
static char	*make_line(t_list *stash)
{
	char	*string;
	int		length;
	int		i;

	length = line_length(stash);
	string = malloc(length + 1);
	if (!string)
		return (NULL);
	copy_line(stash, string);
	i = 0;
	while (string[i])
		i++;
	if (i == 0)
		return (NULL);
	return (string);
}

// Refactor the stash so it starts at the exact place where we left off
// when the function is called again.
static char	*cleanup(t_list **stash)
{
	t_list	*last;
	char	*content;
	int		i;
	int		j;

	last = *stash;
	while (last->next != NULL)
		last = last->next;
	content = malloc(BUFFER_SIZE + 1);
	if (!content)
		return (NULL);
	i = 0;
	j = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	while (last->content[i] != '\0')
		content[j++] = last->content[i++];
	content[j] = '\0';
	return (content);
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;
	char			*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_to_buffer(fd, &stash);
	if (!stash)
		return (NULL);
	line = make_line(stash);
	leftover = cleanup(&stash);
	free_list(stash);
	stash = ft_lstnew(leftover);
	if (leftover[0] == '\0')
	{
		free_list(stash);
		stash = NULL;
	}
	// if (!stash)
	// {
	// 	free(leftover);
	// 	stash = NULL;
	// }
	return (line);
}

// int	main()
// {
//     char	*line;
//     int		fd;
// 	char	buffer[100];

// 	buffer[99] = 0;
//     fd = open("toast", O_RDONLY);
	
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}

// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// read(fd, buffer, 100);
// 	// printf("buffer %s buffer\n", buffer);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);


// 	close(fd);
// 	return (0);
// }
