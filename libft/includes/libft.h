/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:20:19 by kelemayi          #+#    #+#             */
/*   Updated: 2026/03/23 13:43:04 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_LIMIT
#  define OPEN_LIMIT 1024
# endif

# include "../includes/ft_printf.h"
# include "../includes/pipex.h"
# include "../includes/push_swap.h"
# include <stddef.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BOLDRED "\033[1;31m"
# define BOLDGREEN "\033[1;32m"
# define BOLDYELLOW "\033[1;33m"
# define BOLDBLUE "\033[1;34m"
# define BOLDMAGENTA "\033[1;35m"
# define BOLDCYAN "\033[1;36m"
# define RESET "\033[0m"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*******************************************************************************
*			Character_classification_functions		       *
*******************************************************************************/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_issign(int c);
int		ft_isspace(int c);

/*******************************************************************************
*			Character_conversion_functions		               *
*******************************************************************************/
int		ft_toupper(int c);
int		ft_tolower(int c);

/*******************************************************************************
*			String_manipulation_functions:			       *
*******************************************************************************/
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
size_t	ft_strlen_gnl(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_gnl(char *container, char *store_line);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_trimendl(char *str);

/*******************************************************************************
*			Memory_manipulation_funtions:			       *
*******************************************************************************/
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_calloc_gnl(size_t nmemb, size_t size);

/*******************************************************************************
*			File_descriptor_output_funtions:		       *
*******************************************************************************/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*******************************************************************************
*			Read_file_descriptor_functions			       *
*******************************************************************************/
char	*get_next_line(int fd);
char	*get_next_line_bonus(int fd);

/*******************************************************************************
*			Linked_list_funtions:				       *
*******************************************************************************/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
