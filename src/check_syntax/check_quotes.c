/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:44:57 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 11:56:52 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_nbquotes(t_list *lst, int flag)
{
	t_element	*tmp;
	int			i;

	tmp = lst->first;
	i = 0;
	while (tmp)
	{
		if (flag == 0 && tmp->type == DOUBLE_QUOTE && tmp->state != IN_QUOTE)
			i++;
		else if (flag == 1 && tmp->type == QOUTE && tmp->state != IN_DQUOTE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	check_quotes(t_list	*lst)
{
	if (get_nbquotes(lst, 0) % 2 != 0 || \
	get_nbquotes(lst, 1) % 2 != 0)
		return (0);
	return (1);
}

int	is_closed_quote(t_element *elm)
{
	t_element	*tmp;

	tmp = elm->next;
	while (tmp != NULL)
	{
		if (tmp->type == QOUTE)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL && tmp->type == QOUTE)
		return (1);
	return (0);
}

int	is_closed_dquote(t_element *elm)
{
	t_element	*tmp;

	tmp = elm;
	while (tmp)
	{
		if (tmp->type == DOUBLE_QUOTE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
