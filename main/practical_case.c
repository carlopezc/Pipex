/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practical_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:06:13 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/10 12:50:33 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	int	id;
	int	arr[] = { 1, 2, 3, 4, 1, 2, 7 };
	int	arrsize = sizeof(arr) / sizeof(int);
	int	start;
	int	end;
	int	sum;
	int	sumdelchild;
	int	fd[2];
	int	i;
	int	totalsum;

	if (pipe(fd) == -1)
		return (printf("Error in pipe\n"), -1);
	id = fork();
	if (id == -1)
		return (printf("Error in fork\n"), -1);
	if (id != 0)
		wait(NULL);
	if (id == 0)
	{
		start = 0;
		end = arrsize / 2;
	}
	else
	{
		start = arrsize / 2;
		end = arrsize;
	}
	sum = 0;
	i = start;
	while (i < end)
		sum = sum + arr[i++];
	printf("Partial sum %d\n", sum);
	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
		{
			printf("Error writing\n");
			close(fd[1]);
			return (-1);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (read(fd[0], &sumdelchild, sizeof(sum)) == -1)
		{
			printf("Error in read\n");
			close(fd[0]);
			return (-1);
		}
		close(fd[0]);
		totalsum = sum + sumdelchild;
		printf("Total sum es %d\n", totalsum);
	}
	return (0);
}
