/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:16:27 by carlopez          #+#    #+#             */
/*   Updated: 2025/03/12 13:06:52 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h" 

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*src_char;
	unsigned char		*dest_char;

	dest_char = (unsigned char *)dest;
	src_char = (unsigned const char *)src;
	if (!dest_char && !src_char)
		return (dest);
	i = 0;
	while (i < n)
	{
		dest_char[i] = src_char[i];
		i++;
	}
	return (dest_char);
}
