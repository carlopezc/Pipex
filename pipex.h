/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:10:47 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/16 20:37:57 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "printf/ft_printf.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int	fd[2];
	int	docs[2];
	char	*path;
	char	**args;
	int	pid1;
	int	pid2;
}	s_pipex;

void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_free_array(char **arr);
int	ft_manage_pid(int pid, int *fd, char **argv, int flag);
void	ft_close_fd(s_pipex *pipex);

#endif
