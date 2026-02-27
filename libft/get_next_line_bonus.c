/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:58:30 by kelemayi          #+#    #+#             */
/*   Updated: 2024/09/30 13:36:44 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_add_to_container(char *container, char *store_line)
{
	char	*new_cont;

	new_cont = NULL;
	if (!container)
		container = ft_calloc_gnl(sizeof(char), 1);
	new_cont = ft_strjoin_gnl(container, store_line);
	free(container);
	container = NULL;
	return (new_cont);
}

char	*read_file(char *container, int fd)
{
	ssize_t	read_bytes;
	char	*store_line;

	store_line = ft_calloc_gnl(sizeof(char), (BUFFER_SIZE + 1));
	if (!store_line)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, store_line, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(store_line), free(container), NULL);
		store_line[read_bytes] = '\0';
		container = ft_add_to_container(container, store_line);
		if (ft_strchr_gnl(container, '\n'))
			break ;
	}
	free(store_line);
	store_line = NULL;
	return (container);
}

char	*ft_fetch_line(char *container)
{
	char	*line;
	size_t	i;

	i = 0;
	if (container[i] == '\0')
		return (NULL);
	while (container[i] != '\n' && container[i])
		i++;
	line = ft_calloc_gnl(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (container[i] && container[i] != '\n')
	{
		line[i] = container[i];
		i++;
	}
	if (container[i] && container[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_fetch_remains(char *container)
{
	char	*remains;
	size_t	i;
	int		j;

	i = 0;
	while (container[i] && container[i] != '\n')
		i++;
	if (!container[i])
	{
		free (container);
		container = NULL;
		return (NULL);
	}
	remains = ft_calloc_gnl(sizeof(char), (ft_strlen_gnl(container) - i + 1));
	if (!remains)
		return (NULL);
	i++;
	j = 0;
	while (container[i])
		remains[j++] = container[i++];
	free(container);
	container = NULL;
	return (remains);
}

char	*get_next_line_bonus(int fd)
{
	static char	*container[OPEN_LIMIT];
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fd == -42)
	{
		i = 0;
		while (container[i])
		{
			free(container[i]);
			container[i] = NULL;
			i++;
		}
		return (NULL);
	}
	container[fd] = read_file(container[fd], fd);
	if (!container[fd])
		return (NULL);
	line = ft_fetch_line(container[fd]);
	container[fd] = ft_fetch_remains(container[fd]);
	return (line);
}

/* int	main(void)
{
	char	*line, *line1, *line2 = NULL;
	int		fd, fd1, fd2;
	int		i;
	fd = open("text", O_RDONLY);
	fd1 = open("text1", O_RDONLY);
	fd2 = open("text2", O_RDONLY);
	//fd = -1;
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		if (!line && !line1 && !line2)
			break ;
		printf("(row: %d)\n%s\n%s\n%s\n", i, line, line1, line2);
		free(line);
		free(line1);
		free(line2);
		i++;
	}
	close(fd);
	close(fd1);
	close(fd2);
	return (0);
} */
