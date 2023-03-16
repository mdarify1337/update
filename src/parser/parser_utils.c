/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:37:34 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 18:12:49 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_pipe(t_element *elm)
{
	while (elm)
	{
		if (elm->type == PIPE_LINE)
			return (1);
		elm = elm->next;
	}
	return (0);
}	

void	update_redirection(t_cmd_node *cmd, t_element *elm)
{
	t_element	*tmp;

	tmp = elm;
	while (tmp && tmp->type != WORD && tmp->type != ENV)
		tmp = tmp->next;
	if (cmd->io_in != -1 && (elm->type == REDIR_IN || elm->type == HERE_DOC))
		cmd->io_in = open(tmp->content, O_RDONLY, 0644);
	else if (cmd->io_in != -1 && elm->type == REDIR_OUT)
		cmd->io_out = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->io_in != -1 && elm->type == DREDIR_OUT)
		cmd->io_out = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
}
//TODO: add ft_strcat leaks strcpy

char	*ft_realloc(char *old, char *new, t_element *next)
{
	char	*p;

	if (ft_isspace(new[0]) == 1)
	{
		old = ft_strjoin_free(old, " ");
		return (old);
	}
	if (!old)
	{
		old = ft_strdup(new);
		if ((next && next->type != WHITE_SPACE) || (next && next->state == GENERAL))
			old = ft_strjoin_free(old, "*");
		return (old);
	}
	p = malloc((strlen(old) + strlen(new) + 1) * sizeof(char));
	if (p)
	{
		strcpy(p, old);
		strcat(p, new);
		if ((next && next->type != WHITE_SPACE) || (next && next->state == GENERAL))
			p = ft_strjoin_free(p, "*");
	}
	free(old);
	return (p);
}

void	ft_cmdadd_back(t_command **list, t_cmd_node *new)
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
