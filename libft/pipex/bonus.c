/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:12:31 by kel               #+#    #+#             */
/*   Updated: 2024/10/07 14:15:30 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	outgoing_data_pipe(int fds[], char *argv, char *envp[], int fdout)
{
	t_pipex_b	d;

	d.pid = fork();
	if (d.pid == -1)
		ft_fd_error_exit("Error: ", fds, -1, -1);
	if (d.pid == 0)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			ft_fd_exit("Error: ", fds, fdout);
		if (dup2(fdout, STDOUT_FILENO) == -1)
			ft_fd_exit("Error: ", fds, fdout);
		close(fds[0]);
		close(fdout);
		if (!argv || !*argv || ft_isspace(*argv))
			ft_split_exit(argv, fds);
		d.access_cmd = ft_split(argv, ' ');
		ft_access_excec(envp, d.access_cmd, fds, argv);
	}
}

void	incoming_data_pipe(int fds[], char *argv, char *envp[], int fdin)
{
	t_pipex_b	d;

	d.pid = fork();
	if (d.pid == -1)
		ft_fd_error_exit("Error: incoming pipe", fds, -1, -1);
	if (d.pid == 0)
	{
		close(fds[0]);
		if (dup2(fdin, STDIN_FILENO) == -1)
			ft_fd_exit("Error: ", fds, fdin);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			ft_fd_exit("Error: ", fds, fdin);
		close(fds[1]);
		close(fdin);
		if (!argv || !*argv || ft_isspace(*argv))
			ft_split_exit(argv, fds);
		d.access_cmd = ft_split(argv, ' ');
		ft_access_excec(envp, d.access_cmd, fds, argv);
	}
}

void	initial_fds(int argc, char *argv[], t_pipex_b *d, int fds[])
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		if (argc < 6)
			ft_wrong_args("Error heredoc args: ");
		d->i = 3;
		ft_here_doc(argv[2], fds, argc, d->i);
	}
	if (d->i == 3)
	{
		d->fdin = ft_open_fds("here_doc", fds, INFILE);
		d->fdout = ft_open_fds(argv[argc - 1], fds, OUTFILE_APPEND);
	}
	else
	{
		d->i = 2;
		d->fdin = ft_open_fds(argv[1], fds, INFILE);
		d->fdout = ft_open_fds(argv[argc - 1], fds, OUTFILE_TRUNC);
	}
	d->prev_fd = d->fdin;
}

int	main(int argc, char *argv[], char *envp[])
{
	int			fds[2];
	t_pipex_b	d;

	d.i = 0;
	if (argc < 5)
		ft_wrong_args("Error: Wrong number of args");
	initial_fds(argc, argv, &d, fds);
	while (d.i < argc - 2)
	{
		if (pipe(fds) == -1)
			ft_piperror_msg("Error: Pipe failed", fds);
		incoming_data_pipe(fds, argv[d.i++], envp, d.prev_fd);
		close(fds[1]);
		close(d.prev_fd);
		d.prev_fd = fds[0];
	}
	outgoing_data_pipe(fds, argv[argc - 2], envp, d.fdout);
	close(fds[0]);
	wait(NULL);
	wait(NULL);
	close(d.fdin);
	close(d.fdout);
	unlink("here_doc");
	return (0);
}
