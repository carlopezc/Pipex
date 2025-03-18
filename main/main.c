/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:48:45 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/18 15:26:09 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **env)
{
	s_pipex	*pipex;

	if (argc != 5)
		return (ft_printf("Wrong number of arguments\n"), -1);
	if (!env || !*env)
		return (ft_printf("No environment\n"), -1);
	pipex = (s_pipex *)malloc(sizeof(s_pipex));
	if (!pipex)
		return (ft_printf("Error in malloc\n"), -1);
	ft_init_pipex(&pipex);
	if (pipe(pipex->fd) == -1)
		return (ft_printf("Error in pipe\n"), ft_close_fd(pipex), -1);
	if (!ft_check_doc(argv, &pipex))
		return (free(pipex), -1);
	pipex->pid[0] = fork();
	if (!ft_check_fork(pipex, argv, env, 1))
		return (ft_free_struct(pipex), -1);
	pipex->pid[1] = fork();
	if (!ft_check_fork(pipex, argv, env, 2))
		return (ft_free_struct(pipex), -1);
	ft_close_fd(pipex);
	waitpid(pipex->pid[0], NULL, 0);
	waitpid(pipex->pid[1], NULL, 0);
	return (0);
}
