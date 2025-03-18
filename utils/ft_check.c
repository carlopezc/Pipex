/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:15:17 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/18 16:20:30 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_check_doc(char **argv, t_pipex **pipex)
{
	if (access(argv[1], F_OK) != 0)
		return (perror("File doesn't exist\n"), 0);
	if (access(argv[1], R_OK) != 0)
		return (perror("No reading permisson\n"), 0);
	if (access(argv[4], F_OK) != 0)
	{
		if (open(argv[4], O_CREAT, 0777) == -1)
			return (perror("Error creating file\n"), 0);
	}
	if (access(argv[4], W_OK) != 0)
		return (perror("No writing permisson\n"), 0);
	(*pipex)->doc[0] = open(argv[1], O_RDONLY);
	(*pipex)->doc[1] = open(argv[4], O_WRONLY);
	if ((*pipex)->doc[0] == -1 || (*pipex)->doc[1] == -1)
		return (perror("Error opening files\n"), 0);
	return (1);
}

int	ft_check_fork(t_pipex *pipex, char **argv, char **env, int flag)
{
	if (flag == 1)
	{
		if (pipex->pid[0] == -1)
			return (perror("Error in fork\n"), 0);
		if (pipex->pid[0] == 0)
		{
			if (!ft_exec_pid(pipex, argv, env, 1))
				return (0);
		}
	}
	else
	{
		if (pipex->pid[1] == -1)
			return (perror("Error in fork\n"), 0);
		if (pipex->pid[1] == 0)
		{
			if (!ft_exec_pid(pipex, argv, env, 2))
				return (0);
		}
	}
	return (1);
}
