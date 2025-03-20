/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:48:45 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/20 13:05:03 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;

	if (argc != 5)
		return (perror("Wrong number of arguments\n"), -1);
	if (!env || !*env)
		return (perror("No environment\n"), -1);
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		return (perror("Error in malloc\n"), -1);
	ft_init_pipex(&pipex);
	if (pipe(pipex->fd) == -1)
		return (perror("Error in pipe\n"), ft_free_struct(pipex), -1);
	if (!ft_check_doc(argv, &pipex))
		return (ft_free_struct(pipex), -1);
	pipex->pid[0] = fork();
	if (!ft_check_fork(pipex, argv, env, 1))
		return (ft_free_struct(pipex), -1);
	pipex->pid[1] = fork();
	if (!ft_check_fork(pipex, argv, env, 2))
		return (ft_free_struct(pipex), -1);
	ft_close_fd(pipex);
	waitpid(pipex->pid[0], NULL, 0);
	waitpid(pipex->pid[1], NULL, 0);
	return (ft_free_struct(pipex), 0);
}
