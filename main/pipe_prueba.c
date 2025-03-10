/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_prueba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:19:38 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/10 17:15:07 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	int	pid1;

	char	*args[] = {"cat", argv[1], NULL};
	char	*args2[] = {"wc", "-w", NULL};
	char	*path = "/bin/cat";
	char	*path2 = "/bin/wc";
	if (pipe(fd) == -1)
		return (printf("Error in pipe\n"), -1);
	pid1 = fork();
	if (pid1 == -1)
		return (printf("Error in fork\n"), -1);
	if (pid1 == 0)
	{
		//esta en el hijjo
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path, args, NULL);
	}
	int	pid2 = fork();
	if (pid2 == -1)
		return (printf("Error en fork\n"), -1);
	if (pid2 == 0)
	{
		//esta en el hijo 2
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path2, args2, NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	//todo lo demas solo va a poder ser ejecutado por el padre
	return (0);
}
