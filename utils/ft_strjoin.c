/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:22:38 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/12 13:08:58 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	char	*cs1;
	char	*cs2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	cs1 = (char *)s1;
	cs2 = (char *)s2;
	p = (char *)malloc((ft_strlen(cs1) + ft_strlen(cs2) + 1) * sizeof(char));
	if (!p)
		return (0);
	while (i < ft_strlen(cs1))
	{
		p[i] = cs1[i];
		i++;
	}
	while (i < (ft_strlen(cs1) + ft_strlen(cs2)))
		p[i++] = cs2[j++];
	p[i] = '\0';
	return (p);
}
