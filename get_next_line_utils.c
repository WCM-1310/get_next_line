/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warcharo <warcharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:38:04 by warcharo          #+#    #+#             */
/*   Updated: 2024/12/20 02:40:26 by warcharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_list(t_list *list)
{
	t_list	*current;

	while (list)
	{
		current = list;
		list = list->next;
		free(current->content);
		free(current);
	}
}

t_list	*ft_lstnew(char *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!lst || !new)
		return ;
	last_node = *lst;
	while (last_node != NULL && last_node->next != NULL)
		last_node = last_node->next;
	if (!last_node)
		*lst = new;
	else
		last_node->next = new;
}

// Check if the content has new line
int	have_newline(t_list *stash)
{
	int		i;

	if (!stash || !stash->content)
		return (0);
	while (stash->next != NULL)
		stash = stash->next;
	i = 0;
	while (stash->content[i] != '\0')
	{
		if (stash->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// Calculate the total length of character in one line
int	line_length(t_list *stash)
{
	int	i;
	int	length;

	length = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
				return (++length);
			i++;
			length++;
		}
		stash = stash->next;
	}
	return (length);
}
