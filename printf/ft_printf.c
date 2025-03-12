/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:14:31 by carlopez          #+#    #+#             */
/*   Updated: 2024/11/20 16:20:00 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_void(va_list args)
{
	long	arg;

	arg = va_arg(args, unsigned long);
	if (arg == 0)
		return (ft_print_str("(nil)"));
	if (ft_print_str("0x") == -1)
		return (-1);
	return (2 + ft_print_void(arg));
}

static int	ft_check_types(char c, va_list args)
{
	if (c == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (c == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_print_num(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_unsgn_num(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	else if (c == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	else if (c == 'p')
		return (ft_check_void(args));
	else if (c == '%')
		return (ft_print_char('%'));
	return (0);
}

int	ft_printf(char const *c, ...)
{
	va_list	args;
	int		i;
	int		len;
	int		len_check;

	if (!c)
		return (-1);
	va_start(args, c);
	i = -1;
	len = 0;
	while (c[++i] && len > -1)
	{
		if (c[i] == '%' && c[i + 1])
			len_check = ft_check_types(c[++i], args);
		else if (c[i] == '%' && c[i + 1] == '\0')
			len_check = -1;
		else
			len_check = ft_print_char(c[i]);
		if (len_check == -1)
			len = 0;
		len = len + len_check;
	}
	va_end(args);
	return (len);
}
