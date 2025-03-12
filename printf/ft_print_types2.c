/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_types2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:13:37 by carlopez          #+#    #+#             */
/*   Updated: 2024/10/21 13:12:04 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *s)
{
	int	i;

	if (!s)
		return (ft_print_str("(null)"));
	i = 0;
	while (s[i])
		if (ft_print_char(s[i++]) == -1)
			return (-1);
	return (i);
}

int	ft_print_unsgn_num(unsigned int number)
{
	int	len;
	int	num;

	len = 0;
	if (number > 9)
		len += ft_print_unsgn_num(number / 10);
	num = (number % 10) + '0';
	if (ft_print_char(num) == -1)
		return (-1);
	len++;
	return (len);
}

int	ft_print_num(int number)
{
	char	num;
	int		len;

	len = 0;
	if (number == -2147483648)
	{
		if (ft_print_str("-2147483648") == -1)
			return (-1);
		return (11);
	}
	if (number < 0)
	{
		if (ft_print_char('-') == -1)
			return (-1);
		number *= -1;
		len++;
	}
	if (number > 9)
		len += ft_print_num(number / 10);
	num = (number % 10) + '0';
	if (ft_print_char(num) == -1)
		return (-1);
	len++;
	return (len);
}
