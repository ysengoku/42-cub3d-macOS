/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:49:37 by yusengok          #+#    #+#             */
/*   Updated: 2024/02/12 14:03:32 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*s2;

	if (ft_strlen((char *)s1) == 0)
		return (ft_strdup(s1));
	start = 0;
	while (ft_strchr(set, s1[start]) != 0 && s1[start])
		start++;
	end = ft_strlen((char *)s1) - 1;
	while (ft_strchr(set, s1[end]) != 0 && end > start)
		end--;
	s2 = (char *)malloc((end - start + 1) * sizeof(char) + 1);
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1 + start, end - start + 2);
	return (s2);
}
