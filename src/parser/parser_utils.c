/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:37:34 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 12:30:43 by mdarify          ###   ########.fr       */
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

void	ft_check(int fd, char *filename, int flag)
{
	if (fd == -1 && flag)
	{
		ft_putstr_fd("minishell :", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
	else if (fd == -1)
	{
		ft_putstr_fd("minishell :", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : Permission denied\n", 2);
	}
}

void	update_redirection(t_cmd_node *cmd, t_element *elm)
{
	t_element	*tmp;

	tmp = elm;
	while (tmp && tmp->type != WORD && tmp->type != ENV)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (cmd->io_in != -1 && cmd->io_out != -1 && (elm->type == REDIR_IN
			|| elm->type == HERE_DOC))
	{
		cmd->io_in = open(tmp->content, O_RDONLY, 0644);
		ft_check(cmd->io_in, tmp->content, 1);
	}
	else if (cmd->io_in != -1 && cmd->io_out != -1 && elm->type == REDIR_OUT)
	{
		cmd->io_out = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_check(cmd->io_out, tmp->content, 0);
	}
	else if (cmd->io_in != -1 && cmd->io_out != -1 && elm->type == DREDIR_OUT)
	{
		cmd->io_out = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_check(cmd->io_out, tmp->content, 0);
	}
}

char	*ft_realloc(char *old, char *new)
{
	char	*p;

	if (!old)
	{
		old = ft_strdup(new);
		old = ft_strjoin_free(old, " ");
		return (old);
	}
	p = (char *)malloc(strlen(old) + strlen(new) + 1);
	if (p)
	{
		strcpy(p, old);
		strcat(p, new);
		p = ft_strjoin_free(p, " ");
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
