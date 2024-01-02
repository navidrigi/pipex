/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:30:37 by narigi-e          #+#    #+#             */
/*   Updated: 2023/10/25 11:47:25 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/syscall.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

extern char	**environ;

# ifndef ENVP
#  define ENVP environ
# endif

typedef struct s_data
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		fd1;
	int		fd2;
	char	**args1;
	char	**args2;
	char	**envp;
	char	*cmd1;
	char	*cmd1_path;
	char	*cmd2;
	char	*cmd2_path;
	int		status1;
	int		status2;
}				t_data;

/************************************************
************		cleanup.c
**/
void	free_array(char **array);
void	cleanup(t_data *data);
void	free_child_1(t_data *data);
void	free_child_2(t_data *data);

/************************************************
************		ft_putstr_fd.c
**/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

/*************************************************
************		ft_split.c
**/
void	little_calcs(char *str, int *i, char quote);
char	**ft_split(char *str);

/************************************************
************		main.c
**/
t_data	*init_data(char **argv, char **envp);
void	child_1(t_data *data);
void	child_2(t_data *data);
void	parent(t_data *data);

/****************************************************
************		utils_1.c
**/
char	*extract_cmd_name(char *argv);
char	*find_cmd_path(t_data *data, char *cmd);

/****************************************************
************		utils_2.c
**/
void	exit_only(char *str);
void	exit_and_cleanup(t_data *data, char *str);
char	*ft_strdup(char *s1);
void	my_perror(char *str);

/****************************************************
************		utils_3.c
**/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strncpy(char *dest, const char *src, size_t n);

/****************************************************
***********			utils_4.c
***/
void	command_not_found(t_data *data, char *cmd);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_strcpy(char *dest, const char *src);
void	ft_strcat(char *dest, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);

/*************************************************
************		utils_5.c
**/
char	*ft_strndup(const char *s, size_t n);
char	**ft_freeall(char **list);
size_t	ft_wordcount(char const *s, char c);
char	**ft_splitt(char const *s, char c);

#endif
