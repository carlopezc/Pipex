/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:16:15 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/12 11:01:08 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
/*
int	check_file(char *argv, int flag)
{
	int	file;

	if (flag == 1)
		file = open(argv[flag])
}*/

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

char	**build_args(int argc, char **argv, char **split_argv, int flag)
{
	char	**args;
	int	size;
	int	split_size;
	int	i;

	i = 0;
	split_size = 0;
	while (split_argv[i])
	{
		split_size++;
		i++;
	}
	size = split_size + 1;
	if (flag != 1)
		size = size - 1;
	args = (char **)malloc((size + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	args[size--] = NULL;
	/*
	if (check_file(argv[flag]) == -1)
		return (NULL);
		*/
	if (flag == 1)
		args[size--] = argv[flag];
	while (size >= 0 && split_size >= 0)
	{
		args[size] = split_argv[split_size - 1];
		size--;
		split_size--;
	}
	return (args);
}

void	print_data(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		printf("%s\n", data[i]);
		i++;
	}
	return ;
}

int	exec_pid(int fd[2], int argc, char **argv, int flag)
{
	char	**args;
	char	**split_argv;
	char	*path;
	int	file;

	/*
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	*/
	if (flag == 1)
	{
		file = open(argv[1], O_RDONLY);
		if (file == -1)
			return (printf("Error opening file\n"), 0);
		dup2(file, STDIN_FILENO);
		close(file);
		dup2(fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		file = open(argv[4], O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (printf("Error opening file\n"), 0);
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	close(fd[0]); 
	close(fd[1]);
	if (flag == 1)
		split_argv = ft_split(argv[2], ' ');
	else
		split_argv = ft_split(argv[3], ' ');
	if (!split_argv)
		return (printf("Error in split\n"), 0);
	path = ft_strjoin("/bin/", split_argv[0]);
	args = build_args(argc, argv, split_argv, flag);
	if (!args)
		return (printf("Error in malloc\n"), 0);
	//liberar args ycerar fds anes de exit
	if (execve(path, args, NULL) == -1);
		exit(1);
	//faltan liberar todos los args
	return (1);
}

int	main(int argc, char **argv)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (argc != 5)
		return (printf("Wrong number of arguments\n"), -1);
	if (pipe(fd) == -1)
		return (printf("Error in pipe\n"), -1);
	//Primer hijo
	pid1 = fork();
	if (pid1 == -1)
		return (printf("Error in fork\n"), -1);
	if (pid1 == 0)
	{
		//Si esta en el proceso primer hijo entra
		if (!exec_pid(fd, argc, argv, 1))
			return (-1);
	}
	//Segundo hijo
	pid2 = fork();
	if (pid2 == -1)
		return (printf("Error in fork\n"), -1);
	if (pid2 == 0)
	{
		if (!exec_pid(fd, argc, argv, 4))
			return (-1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
