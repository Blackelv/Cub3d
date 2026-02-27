/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:06:42 by kelemayi          #+#    #+#             */
/*   Updated: 2024/10/07 14:15:08 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	outgoing_pipe(int fds[], char *argv[], char *envp[])
{
	t_pipex	vars;

	vars.pid = fork();
	if (vars.pid == -1)
		ft_fd_error_exit("Error outgoing pipe: Fork failed", fds, -1, -1);
	if (vars.pid == 0)
	{
		vars.fdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (vars.fdout == -1)
			ft_file_open_error(argv[4], fds, vars.fdout);
		if (dup2(fds[0], STDIN_FILENO) == -1)
			ft_fd_exit("Error outgoing pipe: Dup2 fds failed", fds, vars.fdout);
		if (dup2(vars.fdout, STDOUT_FILENO) == -1)
			ft_fd_exit("Error outpipe: Dup2 fdout failed", fds, vars.fdout);
		close(fds[0]);
		close(vars.fdout);
		if (!argv[3] || !*argv[3] || ft_isspace(*argv[3]))
			ft_split_exit(argv[3], fds);
		vars.access_cmd = ft_split(argv[3], ' ');
		ft_access_excec(envp, vars.access_cmd, fds, argv[3]);
	}
}

void	incoming_pipe(int fds[], char *argv[], char *envp[])
{
	t_pipex	vars;

	vars.pid = fork();
	if (vars.pid == -1)
		ft_fd_error_exit("Error incoming pipe: Fork failed", fds, -1, -1);
	if (vars.pid == 0)
	{
		close(fds[0]);
		vars.fdin = open(argv[1], O_RDONLY);
		if (vars.fdin == -1)
			ft_file_open_error(argv[1], fds, vars.fdin);
		if (dup2(vars.fdin, STDIN_FILENO) == -1)
			ft_fd_exit("Error incoming pipe: Dup2 fdin failed", fds, vars.fdin);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			ft_fd_exit("Error incoming pipe: Dup2 fds failed", fds, vars.fdin);
		close(fds[1]);
		close(vars.fdin);
		if (!argv[2] || !*argv[2] || ft_isspace(*argv[2]))
			ft_split_exit(argv[2], fds);
		vars.access_cmd = ft_split(argv[2], ' ');
		ft_access_excec(envp, vars.access_cmd, fds, argv[2]);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	fds[2];

	if (argc != 5)
		ft_wrong_args("Error: Wrong number of args");
	if (pipe(fds) == -1)
		ft_piperror_msg("Error: Pipe failed", fds);
	incoming_pipe(fds, argv, envp);
	close(fds[1]);
	outgoing_pipe(fds, argv, envp);
	wait(NULL);
	wait(NULL);
	close(fds[0]);
	return (EXIT_SUCCESS);
}
