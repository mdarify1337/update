/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:51:51 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 18:09:49 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_assign_fname(int length)
{
	int		fd;
	int		t;
	char	*fname;
	int a = 0;

	fname = malloc(sizeof(char) * 15);
	if ((fd = open("/dev/random", O_RDONLY)) == -1)
		return (NULL);
	while (length)
	{
		read(fd, &t, 1);
		t = t % 24;
		fname[a++] = t + 'a';
		length--;
	}
	fname[a] = '\0';
	close(fd);
	return (fname);
}

void	sig_child(int status)
{
	(void)status;
	printf("\n");
	exit(EXIT_FAILURE);//
}

void	here_doc_exec(int fd, t_element *node, int len)
{
	char	*buf;

	signal(SIGINT, &sig_child);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buf = readline(">");
		if (buf == NULL)
			break ;
		if (!ft_strncmp(buf, node->content, len) && \
		ft_strlen(buf) == (size_t)len)
			break ;
		write(fd, ft_strjoin(buf, "\n"), ft_strlen(buf) + 1);
		free(buf);
	}
	close(fd);
	free(buf);
	exit(EXIT_SUCCESS);
}

int	here_doc(t_element *node)
{
	int		fd;
	int		status;
	char	*name;
	int		pid;

	name = ft_strjoin_free2("/private/tmp/", ft_assign_fname(14));
	fd = open(name, O_CREAT | O_RDWR, 777);
	if (fd < 0)
		perror("bad file descriptor");
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		here_doc_exec(fd, node, ft_strlen(node->content));
	waitpid(pid, &status, 0);
	if (status != 0)
		return (0);
	close(fd);
	free(node->content);
	node->content = ft_strdup(name);
	free(name);
	return (1);
}

int	execute_here_doc(t_list **list)
{
	t_element	*node;
	int			index;

	index = -1;
	node = (*list)->first;
	while (node && node->next)
	{
		if (node->type == HERE_DOC && node->next->type != PIPE_LINE)
		{
			while (node && node->type != WORD && node->type != ENV && node->type != WHITE_SPACE)
				node = node->next;
			if (here_doc(node) == 0)
			{
				return (0);
				break ;
			}
		}
		if (node)
			node = node->next;
	}
	return (index);
}
