/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:03 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 11:59:39 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	finitial_variables_commands(t_cmd_node **command, t_helper *value,
		t_env *env)
{
	value->start = 0;
	value->end = 0;
	value->proc = 0;
	value->count = fcalcule_size(*(command)) - 1;
	if (!value->count && fcheck_execv_builtin(*command, env))
		return (0);
	value->fd = malloc(value->count * sizeof(int *));
	value->pid = malloc((value->count + 1) * sizeof(int));
	value->i = 0;
	return (1);
}

void	fpclose_command(t_cmd_node	*fd, t_helper *duplicat)
{
	close(duplicat->fd[duplicat->i - 1][0]);
	close(duplicat->fd[duplicat->i - 1][1]);
	if (duplicat->i < duplicat->count)
	{
		close(duplicat->fd[duplicat->i][0]);
		close(duplicat->fd[duplicat->i][1]);
	}
	dup2(fd->io_in, 0);
}

void	fduplicate_command(t_cmd_node *fd, t_helper *duplicat)
{
	if (fd->io_out > 2)
	{
		if (duplicat->i < duplicat->count)
		{
			close(duplicat->fd[duplicat->i][0]);
			close(duplicat->fd[duplicat->i][1]);
		}
		dup2(fd->io_out, 1);
	}
	else if (duplicat->i != duplicat->count)
	{
		close(duplicat->fd[duplicat->i][0]);
		dup2(duplicat->fd[duplicat->i][1], 1);
		close(duplicat->fd[duplicat->i][1]);
	}
	if (fd->io_in > 2)
		fpclose_command(fd, duplicat);
	else if (duplicat && duplicat->i > 0)
	{
		close(duplicat->fd[duplicat->i - 1][1]);
		dup2(duplicat->fd[duplicat->i - 1][0], 0);
		close(duplicat->fd[duplicat->i - 1][0]);
	}
}

void	fpclose(t_helper *minishell)
{
	if (minishell->i > 0)
	{
		close(minishell->fd[minishell->i - 1][0]);
		close(minishell->fd[minishell->i - 1][1]);
	}
}

void	fprint_ecode(char *s, int fd, int fxcode)
{
	ft_putstr_fd(s, fd);
	g_fcode.exit_status = fxcode;
}
