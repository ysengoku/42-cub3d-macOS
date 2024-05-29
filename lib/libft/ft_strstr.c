/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:37:24 by yusengok          #+#    #+#             */
/*   Updated: 2024/02/12 14:54:28 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen((char *)little);
	if (!little[0])
		return ((char *)big);
	while (big[i + little_len - 1])
	{
		j = 0;
		tmp = i;
		while (big[tmp] == little[j])
		{
			if (!little[j + 1])
				return ((char *)&big[i]);
			j++;
			tmp++;
		}
		i++;
	}
	return (NULL);
}
