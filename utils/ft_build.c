/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:16:47 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/18 16:19:33 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_build_args(t_pipex **pipex, char **argv, int flag)
{
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

	i = 0;
	if (!path_split || !*path_split)
		return ;
	while (path_split[i])
	{
		path = ft_strjoin(path_split[i], ft_strjoin("/", (*pipex)->args[0]));
		if (access(path, X_OK) == 0)
		{
			(*pipex)->path = path;
			return ;
		}
		free(path);
		i++;
	}
	return ;
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
	if (!path_split)
		return ;
	ft_build_path_extra(pipex, path_split);
	return ;
}
