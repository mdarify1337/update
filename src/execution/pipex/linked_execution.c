/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:33:24 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 12:00:52 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	fexecute_command(t_cmd_node *minishell, t_env *env)
{
	if ((find_path(&minishell, env)) == 1)
	{
		g_fcode.exit_status = 127;
	}
	if (minishell->cmd_[0])
	{
		if (execve(minishell->args, minishell->cmd_, convert_array(env)) == -1)
		{
			fprint_ecode("minishell : command not found \n", 2,
				g_fcode.exit_status);
			g_fcode.exit_status = 127;
			exit(g_fcode.exit_status);
		}
	}
}

void	ft_execution_command(t_cmd_node *command, t_env *env)
{
	if (command)
	{
		if (fcalcule_size(command) == 1)
			flinked_execution_command(command, env);
		else if (fcalcule_size(command) > 1)
			flinked_execution_pipex(command, env);
	}
}
