/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:02:10 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/10 16:03:52 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int	file;
	int	pid;

	pid = fork();
	if (pid == -1)
		return (printf("Error in fork\n"), -1);
	if (pid != 0)
		wait(NULL);
	if (pid == 0)
	{
		file = open("prueba.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (printf("Error in file\n"), -1);
		dup2(file, STDOUT_FILENO);
		close(file);
		printf("Esto deberia estar en prueba.txt\n");
	}
	return (0);
}
