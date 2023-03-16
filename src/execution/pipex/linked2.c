/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:24:43 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 11:26:04 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	fchild_command_execution2(t_cmd_node *data, t_env *env, t_helper *val)
{
	t_env_node	*node;
	int			l;

	node = env->first;
	l = 0;
	fduplicate_command(data, val);
	if (fcheck_execv_builtin(data, env))
		exit(g_fcode.exit_status);
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

void	fchild_pipe_execution(t_cmd_node **command, t_helper *val, t_env *env)
{
	if ((*command)->cmd_ && (*command)->cmd_[0])
	{
		val->pid[val->proc] = fork();
		if (val->pid[val->proc] == 0)
		{
			if ((*command)->io_in == -1 || (*command)->io_out == -1)
			{
				g_fcode.exit_status = 1;
				exit(1);
			}
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, &sig_handler);
			fchild_command_execution2(*(command), env, val);
		}
		(val->proc)++;
	}
	fpclose(val);
	if ((*command)->io_in != 0)
		close((*command)->io_in);
	if ((*command)->io_out != 1)
		close((*command)->io_out);
	val->i++;
	*command = (*command)->next;
}

void	fwait_command(t_helper *minishell)
{
	int	l;

	l = 0;
	while (l < minishell->count + 1)
	{
		waitpid(minishell->pid[l], &minishell->status, 0);
		l++;
	}
	if (l == SIGINT)
		g_fcode.exit_status = 130;
	else if (l == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_fcode.exit_status = 131;
	}
	else if (WIFEXITED(l))
		g_fcode.exit_status = WEXITSTATUS(l);
	free(minishell->pid);
}

void	flinked_execution_pipex(t_cmd_node *shell, t_env *env)
{
	t_helper	*value;

	value = malloc(sizeof(t_helper));
	finitial_variables_commands(&shell, value, env);
	while (shell)
	{
		if (value->i < value->count)
		{
			pipe(value->fd[value->i]);
			value->end++;
		}
		fchild_pipe_execution(&shell, value, env);
	}
	fwait_command(value);
	free(value->fd);
	free(value);
}
