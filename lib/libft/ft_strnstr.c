/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:58:06 by yusengok          #+#    #+#             */
/*   Updated: 2024/02/12 14:03:13 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen((char *)little);
	if (!little[0])
		return ((char *)big);
	while (big[i] && i + little_len <= len)
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
