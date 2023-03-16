/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:13:54 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 08:55:06 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lstsize(t_env_node *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_list	*init_tokens(t_list *list)
{
	list = calloc(sizeof(t_list), 1);
	if (!list)
		return (NULL);
	return (list);
}

t_element	*ft_lstnew(char *content, int len, enum e_token type, \
enum e_state state)
{
	t_element	*node;

	node = (t_element *)malloc(sizeof(t_element));
	if (!node)
		return (NULL);
	node->content = ft_strndup(content, len);
	node->len = len;
	node->type = type;
	node->state = state;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

void	ft_lstfree(t_element *list)
{
	free(list->content);
	free(list);
}

void	ft_lstadd_back(t_list **list, t_element *new)
{
	if ((*list)->first == NULL)
		(*list)->first = new;
	else
	{
		(*list)->last->next = new;
		new->previous = (*list)->last;
	}
	(*list)->last = new;
}
