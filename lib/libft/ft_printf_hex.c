/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:34:50 by yusengok          #+#    #+#             */
/*   Updated: 2024/02/12 14:00:41 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_hex(int n, char sp)
{
	unsigned int	nbr;
	int				count;
	char			*base;

	nbr = n;
	if (sp == 'x')
		base = BASE_HEX_LOWER;
	else if (sp == 'X')
		base = BASE_HEX_UPPER;
	if (nbr < 16)
		return (ft_printf_char(base[nbr]));
	count = ft_printf_hex(nbr / 16, sp);
	count += ft_printf_hex(nbr % 16, sp);
	return (count);
}
