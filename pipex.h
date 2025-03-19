/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:10:47 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/19 19:35:11 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "printf/ft_printf.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/wait.h>

typedef struct t_pipex
{
	int		fd[2];
	int		doc[2];
	int		pid[2];
	char	*path;
	char	**args;
}	t_pipex;

void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_free_array(char **arr);
int		ft_manage_pid(int pid, int *fd, char **argv, int flag);
int		ft_check_doc(char **argv, t_pipex **pipex);
int		ft_check_fork(t_pipex *pipex, char **argv, char **env, int flag);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_close_fd(t_pipex *pipex);
void	ft_init_pipex(t_pipex **pipex);
void	ft_free_struct(t_pipex *pipex);
int		ft_exec_pid(t_pipex *pipex, char **argv, char **env, int flag);
void	ft_build_path(t_pipex **pipex, char **env);
int		ft_build_args(t_pipex **pipex, char **argv, int flag);

#endif
