/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:41:51 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/12 13:05:01 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_close_fd(int	*fd)
{
	close(fd[0]);
	close(fd[1]);
	return ;
}

char	**ft_build_args(char **argv, char **split_args, int flag)
{
		char	**args;
		int	size;
		int	split_size;
		int	i;

		i = 0;
		split_size = 0;
		while (split_args[i++])
				split_args++;
		size = split_size + 1;
		if (flag != 1)
				size -= 1;
		args = (char **)malloc((size + 1) * sizeof(char *));
		if (!args)
				return (NULL);
		args[size--] = NULL;
		if (flag == 1)
				args[size--] = argv[flag];
		while (size >= 0 && split_size >= 0)
		{
				args[size] = split_args[split_size - 1];
				size--;
				split_size--;
		}
		return (args);
}

char	**ft_assign_elements(int *file, char **argv, int flag, int *fd)
{
	char	**split_args;

	if (flag == 1)
	{
		*file = open(argv[1], O_RDONLY);
		if (*file == -1)
			return (ft_printf("Error opening file\n"), NULL);
		dup2(*file, STDIN_FILENO);
		close(*file);
		dup2(fd[1], STDOUT_FILENO);
		split_args = ft_split(argv[2], ' ');
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		*file = open(argv[4], O_WRONLY | O_CREAT, 0777);
		if (*file == -1)
			return (ft_printf("Error opening file\n"), NULL);
		dup2(*file, STDOUT_FILENO);
		close(*file);
		split_args = ft_split(argv[3], ' ');
	}
	ft_close_fd(fd);
	return (split_args);
}

int	ft_exec_pid(int *fd, char **argv, int flag)
{
	char	**args;
	char	*path;
	char	**split_args;
	int		file;

	split_args = ft_assign_elements(&file, argv, flag, fd);
	if (!split_args)
		return (0);
	path = ft_strjoin("/bin/", split_args[0]);
	args = ft_build_args(argv, split_args, flag);
	if (!args)
		return (ft_printf("Error building args\n"), 0);
	if (execve(path, args, NULL) == -1)
		return (ft_printf("Error in execve\n"), 0);
	return (ft_free_array(args), 1);
}

int	ft_manage_pid(int pid, int *fd, char **argv, int flag)
{
	if (pid == -1)
		return (ft_printf("Error in fork\n"), 0);
	if (pid == 0)
	{
		if (!ft_exec_pid(fd, argv, flag))
			return (0);
	}
	return (1);
}
