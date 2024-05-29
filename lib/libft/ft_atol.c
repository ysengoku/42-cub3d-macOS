/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 07:51:13 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/23 13:26:45 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_value(const char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (-1);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		i++;
	}
	return (0);
}

long	ft_atol(const char *s)
{
	int			i;
	long long	sign;
	long long	nbr;

	if (check_value(s) == -1)
		return (-1);
	i = 0;
	sign = 1;
	nbr = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		if ((nbr > LONG_MAX / 10)
			|| (sign == 1 && nbr == LONG_MAX / 10 && (s[i] - '0') > 7)
			|| (sign == -1 && nbr == LONG_MAX / 10 && (s[i] - '0') > 7))
			return (-1);
		nbr = nbr * 10 + (s[i] - '0');
		i++;
	}
	return (nbr * sign);
}
