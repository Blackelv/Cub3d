/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:01:02 by kel               #+#    #+#             */
/*   Updated: 2024/10/07 14:15:53 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_fd_error_exit(char *s, int fds[], int fdin, int fdout)
{
	char	*tmp;

	tmp = ft_strdup(s);
	free(tmp);
	if (fds[0] >= 0)
		close(fds[0]);
	if (fds[1] >= 0)
		close(fds[1]);
	if (fdin >= 0)
		close(fdin);
	if (fdout >= 0)
		close(fdout);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_piperror_msg(char *s, int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	perror(s);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_free_mtx(char **mtx)
{
	t_pipex	vars;

	vars.i = 0;
	if (!mtx)
		return ;
	while (mtx[vars.i])
	{
		free(mtx[vars.i]);
		vars.i++;
	}
	free(mtx);
}

char	*path_checks(char **pathmtx, char *cmd)
{
	t_pipex	vars;

	vars.i = 0;
	while (pathmtx[vars.i])
	{
		vars.tmp = ft_strjoin(pathmtx[vars.i], "/");
		vars.path_cmd = ft_strjoin(vars.tmp, cmd);
		free(vars.tmp);
		if (access(vars.path_cmd, F_OK) == 0)
			return (vars.path_cmd);
		free(vars.path_cmd);
		vars.i++;
	}
	return (NULL);
}

char	*path_finder(char *envp[], char *cmd)
{
	t_pipex	vars;

	vars.i = 0;
	while (envp[vars.i] && ft_strncmp(envp[vars.i], "PATH=", 5) != 0)
		vars.i++;
	if (envp[vars.i] == NULL)
	{
		ft_error_msg(cmd);
		return (NULL);
	}
	vars.pathmtx = ft_split(envp[vars.i] + 5, ':');
	if (vars.pathmtx == NULL)
	{
		ft_error_msg("Error: Split failed");
		return (NULL);
	}
	vars.path_cmd = path_checks(vars.pathmtx, cmd);
	ft_free_mtx(vars.pathmtx);
	if (vars.path_cmd)
		return (vars.path_cmd);
	ft_error_msg(cmd);
	return (NULL);
}
