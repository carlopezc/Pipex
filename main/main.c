/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:48:45 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/12 13:10:48 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (argc != 5)
		return (ft_printf("Wrong number of arguments\n"), -1);
	if (pipe(fd) == -1)
		return (ft_printf("Error in pipe\n"), -1);
	pid1 = fork();
	if (!ft_manage_pid(pid1, fd, argv, 1))
		return (ft_close_fd(fd), -1);
	pid2 = fork();
	if (!ft_manage_pid(pid2, fd, argv, 1))
		return (ft_close_fd(fd), -1);
	ft_close_fd(fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
