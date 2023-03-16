/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:26:55 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 12:00:27 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*st_join(char const *s1, char crt, char const *s2)
{
	char	*str;
	size_t	x;
	size_t	y;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[y])
		str[x++] = s1[y++];
	str[x++] = crt;
	y = 0;
	while (s2[y])
		str[x++] = s2[y++];
	str[x] = '\0';
	return (str);
}

char	*check_command(char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	else
	{
		fprint_ecode("minishell : No such file or directory\n", 2,
			g_fcode.exit_status);
		g_fcode.exit_status = 127;
		exit(g_fcode.exit_status);
	}
}

char	*check_command2(char *cmd, t_env *env)
{
	t_env_node	*pwd;
	char		*command;

	pwd = search_by_key(env->first, "PWD");
	command = st_join(pwd->value, '/', cmd);
	if (access(command, X_OK) == 0)
		return (command);
	else
	{
		printf("minishell : %s: Command Not Found\n", cmd);
		g_fcode.exit_status = 127;
		exit(g_fcode.exit_status);
	}
}

char	*get_cmd(char **paths, char *cmd, t_env *env)
{
	char		**tmp;
	char		*command;

	if (cmd[0] == '/')
		check_command(cmd);
	else if (cmd[0] == '.')
		check_command2(cmd, env);
	else
	{
		tmp = paths;
		while (*tmp != NULL)
		{
			command = st_join(*tmp, '/', cmd);
			tmp++;
			if (access(command, X_OK) == 0)
			{
				free_2d_array(paths);
				return (command);
			}
			free(command);
		}
	}
	free_2d_array(paths);
	return (NULL);
}

int	find_path(t_cmd_node **cmd, t_env *env)
{
	t_env_node	*node;
	char		*abs_path;

	node = search_by_key(env->first, "PATH");
	if (!node)
		return (0);
	abs_path = get_cmd(ft_split(node->value, ':'), (*cmd)->args, env);
	if (abs_path == NULL)
	{
		fprint_ecode("minishell : command not found\n", 2, 127);
		g_fcode.exit_status = 127;
		exit(127);
	}
	else if (abs_path)
	{
		free((*cmd)->args);
		(*cmd)->args = ft_strdup(abs_path);
		free(abs_path);
		return (1);
	}
	return (g_fcode.exit_status);
}
