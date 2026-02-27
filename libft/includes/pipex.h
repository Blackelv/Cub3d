/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:25:12 by kelemayi          #+#    #+#             */
/*   Updated: 2024/09/30 09:48:45 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../includes/libft.h"

typedef struct pipex
{
	pid_t	pid;
	int		fdin;
	int		fdout;
	int		i;
	char	**cmd;
	char	**access_cmd;
	char	*path_cmd;
	char	*tmp;
	char	**pathmtx;
}	t_pipex;

typedef struct pipex_bonus
{
	int		i;
	int		fdin;
	int		fdout;
	int		fdhd;
	int		prev_fd;
	int		here_doc;
	int		pipe_count;
	int		file;
	char	*line;
	char	**access_cmd;
	pid_t	pid;

}	t_pipex_b;

typedef enum open_fd
{
	INFILE,
	OUTFILE_TRUNC,
	OUTFILE_APPEND,
}	t_open_fd;

// main.c
void	outgoing_pipe(int fds[], char *argv[], char *envp[]);
void	incoming_pipe(int fds[], char *argv[], char *envp[]);
//int		main(int argc, char *argv[], char *envp[]);
// utils.c
void	ft_wrong_args(char *s);
void	ft_error_msg(char *s);
void	ft_split_exit(char *s, int fds[]);
void	ft_file_open_error(char *argv, int fd[2], int fdinout);
void	ft_fd_exit(char *s, int fds[], int fd);

// more_utils.c
char	*path_finder(char *envp[], char *cmd);
char	*path_checks(char **pathmtx, char *cmd);
void	ft_free_mtx(char **mtx);
void	ft_piperror_msg(char *s, int fd[2]);
void	ft_fd_error_exit(char *s, int fds[], int fdin, int fdout);

// utils_bonus.c
void	ft_here_doc(char *limiter, int fds[], int argc, int i);
int		ft_open_fds(char *argv, int fds[], t_open_fd mode);
void	prep_cmds(char *envp[], char *args, int fds[]);
void	ft_access_excec(char *envp[], char *access_cmd[], int fds[], char *av);
#endif
