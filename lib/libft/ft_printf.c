/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:47:32 by yusengok          #+#    #+#             */
/*   Updated: 2024/02/12 14:00:09 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_specifiers(const char *format);
static int	ft_print_arg(const char *format, int i, va_list ap);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		n;
	int		i;

	if (!format || !ft_check_specifiers(format))
		return (-1);
	va_start(ap, format);
	count = 0;
	i = 0;
	while (format[i++] != '\0')
	{
		if (format[i - 1] != '%')
			n = (int)write(1, &format[i - 1], 1);
		else if (format[i - 1] == '%')
			n = ft_print_arg(format, i++, ap);
		if (n < 0)
		{
			va_end(ap);
			return (-1);
		}
		count += n;
	}
	va_end(ap);
	return (count);
}

static int	ft_check_specifiers(const char *format)
{
	size_t	i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
				i++;
			else if (!ft_strchr(SPECIFIERS, format[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_print_arg(const char *format, int i, va_list ap)
{
	if (format[i] == 'c')
		return (ft_printf_char(va_arg(ap, int)));
	if (format[i] == 's')
		return (ft_printf_str(va_arg(ap, char *)));
	if (format[i] == 'p')
		return (ft_printf_ptr(va_arg(ap, void *)));
	if (format[i] == 'd' || format[i] == 'i')
		return (ft_printf_nbr(va_arg(ap, int)));
	if (format[i] == 'u')
		return (ft_printf_uint(va_arg(ap, int)));
	if (format[i] == 'x' || format[i] == 'X')
		return (ft_printf_hex(va_arg(ap, int), format[i]));
	if (format[i] == '%')
		return (write(1, "%", 1));
	return (-1);
}
