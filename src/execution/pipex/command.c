/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:37 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 16:18:21 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	fbuilt_command_right(t_cmd_node *info, t_env *env)
{
	int	fd;

	if (fcommand_built(info))
	{
		if (info->io_in > 2)
		{
			fd = dup(1);
			dup2(info->io_in, 1);
		}
		if (fcheck_execv_builtin(info, env))
		{
			if (info->io_out > 2)
			{
				dup2(fd, 1);
				close(info->io_out);
				close(fd);
			}
			return (1);
		}
	}
	return (0);
}

void	fcheck_valid_fd(t_cmd_node *fd, t_helper *duplicat)
{
	if (fd->io_in == -1 || fd->io_out == -1)
	{
		g_fcode.exit_status = 1;
		exit(g_fcode.exit_status);
	}
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, &sig_handler);
	if (fd->io_out > 2)
		dup2(fd->io_out, 1);
	else if (duplicat)
		dup2(duplicat->fd[duplicat->i][1], 1);
	if (fd->io_in > 2)
		dup2(fd->io_in, 0);
	else if (duplicat && duplicat->i != 0)
		dup2(duplicat->fd[duplicat->i - 1][0], 0);
}

void	fchild_command_execution(t_cmd_node *data, t_env *env, t_helper *val)
{
	t_env_node	*node;
	int			l;

	node = env->first;
	l = fork();
	if (l == 0)
	{
		fcheck_valid_fd(data, val);
		if (fcheck_execv_builtin(data, env))
			exit(g_fcode.f_command->fcd);
		while (node)
		{
			if (!ft_strcmp(node->key, "PATH"))
				break ;
			node = node->next;
		}
		if (!env && !ft_strchr(data->cmd_[0], '/'))
			flinked_send_error(2, data->cmd_[0]);
		if (!ft_strchr(data->cmd_[0], '/'))
			fexecute_command(data, env);
		else
			fexecute_command(data, env);
	}
}

void	flinked_execution_command(t_cmd_node *command, t_env *env)
{
	int	l;

	if (fbuilt_command_right(command, env))
		return ;
	if (command->cmd_ && command->args)
		fchild_command_execution(command, env, NULL);
	if (command->io_in > 2)
		close(command->io_in);
	if (command->io_out > 2)
		close(command->io_out);
	g_fcode.exit_status = 0;
	wait(&l);
	if (l == SIGINT)
		g_fcode.exit_status = 130;
	else if (l == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_fcode.exit_status = 131;
	}
	else if (WIFEXITED(l))
		g_fcode.exit_status = WEXITSTATUS(l);
}
