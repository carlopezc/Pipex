/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:35:28 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/10 11:57:57 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	int	id;
	int	y;

	//fd[0] read
	//fd[1] write
	if (pipe(fd) == -1)
		return (printf("Error\n"));
	id = fork();
	if (id == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (printf("Error with fork\n"), -1);
	}
	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], "5", 1) == -1)
		{
			printf("Error while using write\n");
			close(fd[1]);
			return (-1);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("Error while reading\n");
			close(fd[0]);
			return (-1);
		}
		close(fd[0]);
		printf("%c\n", y);
	}
	return (0);
}
