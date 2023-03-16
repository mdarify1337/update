/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:51:51 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 12:34:21 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_assign_fname(int length)
{
	char	*fname;
	int		fd;
	int		t;
	int		a;

	a = 0;
	fname = malloc(sizeof(char) * 15);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
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

void	here_doc(t_element *node)
{
	char	*buf;
	int		fd;
	int		len;
	char	*name;

	len = ft_strlen(node->content);
	name = ft_strjoin("/private/tmp/", ft_assign_fname(14));
	fd = open(name, O_CREAT | O_RDWR, 777);
	if (fd < 0)
		perror("bad file descriptor");
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
	free(node->content);
	node->content = ft_strdup(name);
	free(name);
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
			while (node && node->type != WORD && node->type != ENV)
				node = node->next;
			if (node != NULL)
				here_doc(node);
		}	
		node = node->next;
	}
	return (index);
}
