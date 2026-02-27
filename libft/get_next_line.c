/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:03:34 by kelemayi          #+#    #+#             */
/*   Updated: 2024/09/30 14:29:39 by kelemayi         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char	*container = NULL;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fd == -42)
	{
		free(container);
		container = NULL;
		return (NULL);
	}
	container = read_file(container, fd);
	if (!container)
		return (NULL);
	line = ft_fetch_line(container);
	container = ft_fetch_remains(container);
	return (line);
}

/*int	main(void)
{
	char	*line = NULL;
	int		fd;
	int		i;
	fd = 0;
	//fd = open("text", O_RDONLY);
	//fd = -1;
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("(row: %d)\n%s\n", i, line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}*/

/* int	main(void)
{
	//char	*line = NULL;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	printf("GNL 1: %s", get_next_line(fd));
	printf("GNL 2: %s", get_next_line(fd));
	printf("GNL 3: %s", get_next_line(fd));
	printf("GNL 4: %s", get_next_line(fd));
	// printf("GNL 5: %s", get_next_line(fd));
	// printf("GNL 6: %s", get_next_line(fd));
	// printf("GNL 7: %s", get_next_line(fd));
	// printf("GNL 8: %s", get_next_line(fd));
	// printf("GNL 9: %s", get_next_line(fd));
	// printf("GNL 10: %s", get_next_line(fd));
	// printf("GNL 11: %s", get_next_line(fd));
	// printf("GNL 12: %s", get_next_line(fd));
	// printf("GNL 13: %s", get_next_line(fd));
	close(fd);
	return (0);
} */
