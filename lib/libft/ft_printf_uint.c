/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:52:58 by yusengok          #+#    #+#             */
/*   Updated: 2024/02/12 14:00:18 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_digits_count(long n);

int	ft_printf_uint(int n)
{
	unsigned int	nbr;
	char			*digits;
	int				len;
	int				count;

	nbr = (unsigned int)n;
	len = ft_get_digits_count((long)nbr);
	digits = (char *)ft_calloc(len + 1, sizeof(char));
	if (!digits)
		return (-1);
	if (nbr == 0)
		digits[--len] = '0';
	while (nbr > 0)
	{
		digits[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	count = ft_printf_str(digits);
	free(digits);
	return (count);
}

static int	ft_get_digits_count(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += 1;
		n *= -1;
	}
	if (n == 0)
		count = 1;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}
