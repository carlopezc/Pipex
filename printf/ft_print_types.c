/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:13:37 by carlopez          #+#    #+#             */
/*   Updated: 2024/11/20 15:53:37 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h" 

static int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

static int	ft_print_uppercase(char c)
{
	if (ft_isalpha(c))
		c = c - 32;
	return (ft_print_char(c));
}

int	ft_print_hex(unsigned int number, int flag)
{
	char	towrite;
	int		len;

	len = 0;
	if (number / 16 > 0)
		len += ft_print_hex(number / 16, flag);
	len++;
	if (number % 16 > 9)
		towrite = ((number % 16) - 10) + 'a';
	else
		towrite = number % 16 + '0';
	if (flag == 0)
	{
		if (ft_print_char(towrite) == -1)
			return (-1);
	}
	else if (flag == 1)
	{
		if (ft_print_uppercase(towrite) == -1)
			return (-1);
	}
	return (len);
}

int	ft_print_void(unsigned long address)
{
	char	towrite;
	int		len;

	len = 0;
	if (address / 16 > 0)
		len += ft_print_void(address / 16);
	len++;
	if (address % 16 > 9)
		towrite = ((address % 16) - 10) + 'a';
	else
		towrite = address % 16 + '0';
	if (ft_print_char(towrite) == -1)
		return (-1);
	return (len);
}
