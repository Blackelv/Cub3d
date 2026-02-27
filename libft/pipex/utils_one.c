/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:57:34 by kel               #+#    #+#             */
/*   Updated: 2024/10/07 14:15:46 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_wrong_args(char *s)
{
	errno = EINVAL;
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	perror(s);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_error_msg(char *s)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("-->: Command not found: ", STDERR_FILENO);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
}

void	ft_split_exit(char *s, int fds[])
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("-->: Command not found: ", STDERR_FILENO);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	if (fds[0] >= 0)
		close(fds[0]);
	if (fds[1] >= 0)
		close(fds[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_file_open_error(char *argv, int fd[2], int fdinout)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	perror(argv);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
	if (fdinout >= 0)
		close(fdinout);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_fd_exit(char *s, int fds[], int fd)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	perror(s);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	if (fd >= 0)
		close(fd);
	if (fds[0] >= 0)
		close(fds[0]);
	if (fds[1] >= 0)
		close(fds[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}
