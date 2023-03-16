/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:07:24 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 11:27:38 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_ctlc(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &t);
}

int	ft_readline(char **line)
{
	signal(SIGINT, &sig_handler);
	*line = readline("minishell$> ");
	signal(SIGINT, SIG_IGN);
	if (!(*line))
	{
		write(2, "exit\n", 5);
		exit (g_fcode.exit_status);
	}
	if (ft_strcmp(*line, "") == -1 || ft_strisspace(*line))
		return (1);
	if (strlen(*line) > 0)
		add_history(*line);
	return (0);
}

void	free_cmd(t_cmd_node **cmd)
{
	t_cmd_node	*tmp;
	int			i;

	while (*cmd)
	{
		i = 0;
		tmp = (*cmd)->next;
		while ((*cmd) && (*cmd)->cmd_[i])
		{
			free((*cmd)->cmd_[i]);
			i++;
		}
		free((*cmd)->cmd_);
		free((*cmd)->args);
		free(*cmd);
		*cmd = tmp;
	}
}

void	minishell(char **envv)
{
	char		*line;
	t_list		*element;
	t_env		*env;
	t_command	*cmd;

	line = NULL;
	env = ft_init_env(envv);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler);
	remove_ctlc();
	while (1)
	{
		if (ft_readline(&line))
		{
			free(line);
			continue ;
		}
		element = lexer(line);
		execute_here_doc(&element);
		check_syntax(element);
		ft_expand(&element, env);
		cmd = parse_command(&element);
		ft_split_args(&cmd->first);
		ft_execution_command(cmd->first, env);
		ft_parsing_cleaner(element, cmd->first, env);
		free(cmd);
	}
}
