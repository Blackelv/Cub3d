/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:13:36 by kel               #+#    #+#             */
/*   Updated: 2024/10/07 14:15:39 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_here_doc(char *limiter, int fds[], int argc, int i)
{
	t_pipex_b	d;

	d.fdhd = ft_open_fds("here_doc", fds, OUTFILE_APPEND);
	if (d.fdhd == -1)
		ft_file_open_error("here_doc", fds, d.fdhd);
	while (1)
	{
		d.pipe_count = i;
		while (d.pipe_count++ < argc -2)
			ft_putstr_fd("pipe ", STDOUT_FILENO);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		d.line = get_next_line(STDIN_FILENO);
		if (!d.line)
			ft_fd_exit("Error gnl: ", fds, d.fdhd);
		if (ft_strncmp(d.line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(d.line) - 1 == ft_strlen(limiter))
		{
			free(d.line);
			break ;
		}
		ft_putstr_fd(d.line, d.fdhd);
		free(d.line);
	}
	get_next_line(-42);
	close(d.fdhd);
}

int	ft_open_fds(char *argv, int fds[], t_open_fd mode)
{
	t_pipex_b	data;

	if (mode == INFILE)
		data.file = open(argv, O_RDONLY, 0777);
	else if (mode == OUTFILE_TRUNC)
		data.file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == OUTFILE_APPEND)
		data.file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (data.file == -1)
		ft_file_open_error("Error opening file: ", fds, data.file);
	return (data.file);
}

void	prep_cmds(char *envp[], char *args, int fds[])
{
	t_pipex	vars;

	vars.i = 0;
	vars.cmd = ft_split(args, ' ');
	if (!vars.cmd || !vars.cmd[0])
	{
		ft_free_mtx(vars.cmd);
		ft_split_exit(args, fds);
	}
	vars.path_cmd = path_finder(envp, vars.cmd[0]);
	if (vars.path_cmd == NULL)
	{
		ft_free_mtx(vars.cmd);
		ft_fd_error_exit("Error prep_cmds: Path not found", fds, -1, -1);
	}
	if (execve(vars.path_cmd, vars.cmd, envp) == -1)
	{
		ft_free_mtx(vars.cmd);
		free(vars.path_cmd);
		ft_fd_error_exit("Error prep_cmds: Execve failed", fds, -1, -1);
	}
	ft_free_mtx(vars.cmd);
	free(vars.path_cmd);
}

void	ft_access_excec(char *envp[], char *access_cmd[], int fds[], char *argv)
{
	if (access(access_cmd[0], F_OK) == -1)
	{
		ft_free_mtx(access_cmd);
		prep_cmds(envp, argv, fds);
	}
	else
	{
		execve(access_cmd[0], access_cmd, envp);
		ft_free_mtx(access_cmd);
		ft_fd_error_exit("--> permission denied \n" RESET, fds, -1, -1);
	}
}
