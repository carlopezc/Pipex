/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:16:47 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/20 13:25:24 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_build_args(t_pipex **pipex, char **argv, int flag)
{
	if (!argv[2] || !argv[3])
		return (0);
	if (flag == 1)
		(*pipex)->args = ft_split(argv[2], ' ');
	else
		(*pipex)->args = ft_split(argv[3], ' ');
	if (!(*pipex)->args)
		return (0);
	return (1);
}

void	ft_build_path_extra(t_pipex **pipex, char **path_split)
{
	int		i;
	char	*path;
	char	*initial_path;

	i = 0;
	while (path_split[i])
	{
		initial_path = ft_strjoin("/", (*pipex)->args[0]);
		if (!initial_path)
			return (ft_free_array(path_split));
		path = ft_strjoin(path_split[i], initial_path);
		if (!path)
			return (free(initial_path), ft_free_array(path_split));
		if (access(path, X_OK) == 0)
		{
			(*pipex)->path = path;
			return (free(initial_path), ft_free_array(path_split));
		}
		free(path);
		free(initial_path);
		i++;
	}
	return (ft_free_array(path_split));
}

void	ft_build_path(t_pipex **pipex, char **env)
{
	char	**path_split;
	int		i;

	if (!env || !*env)
		return ;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=/", 6) == 0)
		{
			path_split = ft_split(env[i] + 6, ':');
			break ;
		}
		i++;
	}
	if (!path_split || !*path_split)
		return ;
	ft_build_path_extra(pipex, path_split);
	return ;
}
