/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:31:17 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/17 12:20:43 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h" 

static size_t	ft_nword(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

void	ft_free_array(char **arr)
{
	size_t	j;

	j = 0;
	while (arr[j])
		free(arr[j++]);
	free(arr);
	return ;
}

static char	**ft_fill_array(char **arr, char const *s, char c, size_t len)
{
	size_t			j;
	size_t			i;
	unsigned int	start;

	i = 0;
	j = 0;
	start = 0;
	while (j < len)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			arr[j] = ft_substr(s, start, i - start);
			if (!arr[j])
				return (ft_free_array(arr), NULL);
		}
		j++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_nword(s, c);
	arr = (char **)malloc((len + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_fill_array(arr, s, c, len);
	return (arr);
}
