/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:27:27 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/10 11:29:58 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	main(void)
{
	int	id1;
	int	id2;
	
	id1 = fork();
	id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
			printf("Es el hijo del hijo del padre, proceso y\n");
		else
			printf("Es el hijo del padre con hijos, proceso x\n");
	}
	else
	{
		if (id2 == 0)
			printf("Es el hijo del padre sin hijos, proceso z\n");
		else
			printf("Es el padre\n");
	}
	while (wait(NULL) != -1 || errno != ECHILD)
		printf("ha esperado a un hijo\n");
	return (0);
}
