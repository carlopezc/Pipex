/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:41:51 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/16 20:27:52 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_close_fd(s_pipex *pipex)
{
	close((pipex->fd)[0]);
	close((pipex->fd)[1]);
	return ;
}

char	**ft_build_args(s_pipex	**pipex, char **argv, char **split_args, int flag)
{
		char	**args;
		int	size;
		int	i;

		i = 0;
		size = 0;
		while (split_args[i++])
				size++;
		args = (char **)malloc((size + 1) * sizeof(char *));
		if (!args)
				return (NULL);
		args[size--] = NULL;
		while (size >= 0)
		{
			args[size] = split_args[size - 1];
			size--;
		}
		return (args);
}

char	**ft_assign_elements(s_pipex *pipex, char **argv, int flag)
{
	char	**split_args;

	if (flag == 1)
	{
		dup2((pipex->docs)[0], STDIN_FILENO);
		close((pipex->docs)[0]);
		dup2((pipex->fd)[1], STDOUT_FILENO);
		split_args = ft_split(argv[2], ' ');
	}
	else
	{
		dup2((pipex->fd)[0], STDIN_FILENO);
		dup2((pipex->docs)[1], STDOUT_FILENO);
		close((pipex->docs)[1]);
		split_args = ft_split(argv[3], ' ');
	}
	ft_close_fd(pipex);
	return (split_args);
}

int	ft_check_docs(char **argv, s_pipex *pipex)
{
	if (access(argv[1], F_OK) != 0)
		return (ft_printf("File doesn't exit\n"), 0);
	if (access(argv[1], R_OK) != 0)
		return (ft_printf("No reading permisson\n"), 0);
	if (access(argv[4], F_OK) != 0)
	{
		if (open(argv[4], O_CREAT, 0777) == -1)
			return (ft_printf("Error creating file\n"), 0);
	}
	if (access(argv[4], W_OK) != 0)
		return (ft_printf("No writing permisson\n"), 0);
	pipex->docs[0] = open(argv[1], O_RDONLY);
	pipex->docs[1] = open(argv[4], O_WRONLY);
	if (pipex->docs[0] == -1 || pipex->docs[1] == -1)
		return (ft_printf("Error opening files\n"),  0);
	return (1);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	ft_build_path_extra(s_pipex **pipex, char **path_split, char **argv, int flag)
{
	int	i;
	char	*path;

	i = 0;
	if (!path_split || !*path_split)
		return ;
	while (path_split[i])
	{
		path = ft_strjoin(path_split[i], ft_strjoin("/", argv[flag]));
		if (access(path, X_OK) == 0)
		{
			free(path);
			(*pipex)->path = path_split[i];
			return ;
		}
		free(path);
		i++;
	}
	return ;
}

void	ft_build_path(s_pipex **pipex, char **env, char **argv, int flag)
{
	char	**path_split;
	int	i;

	if (!env ||  !*env)
		 return ;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=/", 6) == 0)
		{
			path_split = ft_split(env[i] + 6, ":");
			break ;
		}
		i++;
	}
	i = 0;
	if (!path_split)
		return ;
	ft_build_path_extra(pipex, path_split, argv, flag);
	return (ft_free_array(path_split));
}

int	ft_exec_pid(s_pipex *pipex, char **argv, char **env, int flag)
{
	char	**args;
	char	*path;
	char	**split_args;
	int		*docs;

	split_args = ft_assign_elements(pipex, argv, flag);
	if (!split_args)
		return (0);
	ft_build_path(&pipex, env, argv);
	ft_build_args(&pipex, argv, split_args, flag);
	if (!pipex->path || !pipex->args)
		return (ft_printf("Error building args\n"), 0);
	if (execve(pipex->path, pipex->args, NULL) == -1)
		return (ft_printf("Error in execve\n"), 0);
	return (ft_free_array(args), 1);
}

int	ft_check_fork(s_pipex *pipex, char **argv, char **env, int flag)
{
	if (flag == 1)
	{
		if (pipex->pid1 == -1)
			return (ft_printf("Error in fork\n"), 0);
		if (pipex->pid1 == 0)
		{
			if (!ft_exec_pid(pipex, argv, env, 1))
				return (0);
		}
	}
	else
	{
		if (pipex->pid2 == -1)
			return (ft_printf("Error in fork\n"), 0);
		if (pipex->pid2 == 0)
		{
			if (!ft_exec_pid(pipex, argv, env, 2))
				return (0);
		}
	}
	return (1);
}
