/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:43:45 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/11 13:05:35 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_memcpy(void *dest, void *src, size_t n);
size_t	ft_strlen(char *str);

char	*ft_strdup(char *s)
{
	char	*p;
	size_t	len;

	len = ft_strlen(s);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	ft_memcpy(p, s, len);
	p[len] = '\0';
	return (p);
}
