/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:41:51 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/18 16:18:32 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free_struct(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex)
		return ;
	free(pipex->path);
	while (pipex->args && pipex->args[i])
		free(pipex->args[i++]);
	ft_close_fd(pipex);
	free(pipex);
}

void	ft_close_fd(t_pipex *pipex)
{
	close((pipex->fd)[0]);
	close((pipex->fd)[1]);
	return ;
}

void	ft_init_pipex(t_pipex **pipex)
{
	if (!pipex || !*pipex)
		return ;
	(*pipex)->fd[0] = -1;
	(*pipex)->fd[1] = -1;
	(*pipex)->doc[0] = -1;
	(*pipex)->doc[1] = -1;
	(*pipex)->path = NULL;
	(*pipex)->args = NULL;
	(*pipex)->pid[0] = -1;
	(*pipex)->pid[1] = -1;
	return ;
}

void	ft_dup_fd(t_pipex *pipex, int flag)
{
	if (flag == 1)
	{
		dup2((pipex->doc)[0], STDIN_FILENO);
		close((pipex->doc)[0]);
		dup2((pipex->fd)[1], STDOUT_FILENO);
	}
	else
	{
		dup2((pipex->fd)[0], STDIN_FILENO);
		dup2((pipex->doc)[1], STDOUT_FILENO);
		close((pipex->doc)[1]);
	}
	ft_close_fd(pipex);
	return ;
}

int	ft_exec_pid(t_pipex *pipex, char **argv, char **env, int flag)
{
	ft_dup_fd(pipex, flag);
	ft_build_args(&pipex, argv, flag);
	ft_build_path(&pipex, env);
	if (!pipex->path || !pipex->args)
		return (perror("Error building args\n"), 0);
	if (execve(pipex->path, pipex->args, env) == -1)
		return (perror("Error in execve\n"), 0);
	return (1);
}
