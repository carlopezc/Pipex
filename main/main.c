/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:48:45 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/16 20:35:57 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **env)
{
	s_pipex	*pipex;

	if (argc != 5)
		return (ft_printf("Wrong number of arguments\n"), -1);
	pipex = (s_pipex *)malloc(sizeof(s_pipex));
	if (!pipex)
		return (ft_printf("Error in malloc\n"), -1);
	if (pipe(pipex->fd) == -1)
		return (ft_printf("Error in pipe\n"), ft_close_fd(pipex), -1);
	if (!ft_check_docs(argv, pipex))
		return (free(pipex), -1);
	pipex->pid1 = fork();
	if (!ft_check_fork(pipex, argv, env, 1))
		return (free(pipex->docs), free(pipex), ft_free_array(pipex->args), -1);
	pipex->pid2 = fork();
	if (!ft_check_fork(pipex, argv, env, 2))
		return (free(pipex->docs), free(pipex), ft_free_array(pipex->args), -1);
	ft_close_fd(pipex);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
