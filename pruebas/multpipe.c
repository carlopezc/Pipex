/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:17:44 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/10 18:23:15 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	int fd[3][2];
	int	i;

	while (i < 3)
	{
		if (pipe(fd[i]) == -1)
			return (printf("Error in pipes\n"), -1);
		i++;
	}
	//primer hijo
	int pid1 = fork();
	if (pid1 == -1)
		return (printf("Error in fork\n"), -1);
	if (pid1 == 0)
	{
		//Proceso hijo 1, vamos a usar el 01 y 20
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		int	x;
		if (read(fd[0][0], &x, sizeof(int)) == -1)
			return (printf("Error reading\n"), -1);
		x = x + 5;
		if (write(fd[1][1], &x, sizeof(int)) == -1)
				return ("Error writing\n", -1);
		close(fd[0][0]);
		close(fd[1][1]);
	}
	int pid2 = fork();
	if (pid2 == -1)
		return (printf("Error in fork\n"), -1);
	if (pid2 == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int	y;
		if (read(fd[1][0], &y, sizeof(int)) == -1)
			return (-1);
		y = y + 5;
		if (write(fd[2][1], &y, sizeof(int)) == -1)
				return ("Error writing\n", -1);
		close(fd[1][0]);
		close(fd[2][1]);
	}
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	int	z;
	z = 0;
	if (write(fd[0][1], &z, sizeof(int)) == -1)
		return (-1);
	if (read(fd[2][0], &z, sizeof(int)) == -1)
		return (-1);
	printf("Result is %d\n", z);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close(fd[2][0]);
	close(fd[0][1]);
	return (0);
}
