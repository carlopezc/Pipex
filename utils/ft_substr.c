/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:42:39 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/12 13:10:08 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	str_len;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	str_len -= start;
	if (str_len > len)
		str_len = len;
	p = (char *)malloc((str_len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < str_len && s[start])
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
