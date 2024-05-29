/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:56:47 by yusengok          #+#    #+#             */
/*   Updated: 2024/02/26 14:07:42 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr_r(char *big, char *little)
{
	int	i;
	int	j;
	int	little_len;

	little_len = ft_strlen(little);
	i = ft_strlen(big) - little_len;
	if (i < 0)
		return (big);
	j = 0;
	while (big[i] && little[j])
	{
		if (big[i] != little[j])
			return (&big[i]);
		i++;
		j++;
	}
	return (NULL);
}
