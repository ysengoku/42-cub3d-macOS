/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:50:03 by yusengok          #+#    #+#             */
/*   Updated: 2024/02/12 14:01:38 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_wordcount(char const *s, char c);
static void		ft_freeall(char **str, size_t i);
static char		**ft_cpy_words(char const *s, char c, size_t count, char **arr);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	wordcount;

	if (!s)
		return (NULL);
	wordcount = ft_get_wordcount(s, c);
	arr = malloc((wordcount + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (ft_cpy_words(s, c, wordcount, arr));
}

static size_t	ft_get_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (0);
	count = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1])
				count++;
		}
		i++;
	}
	return (count);
}

static void	ft_freeall(char **str, size_t i)
{
	while ((int)i >= 0)
		free(str[i--]);
	free(str);
}

static char	**ft_cpy_words(char const *s, char c, size_t count, char **arr)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (i < count)
	{
		while (s[j] && s[j] == c)
			j++;
		start = j;
		while (s[j] && s[j] != c)
			j++;
		arr[i] = ft_substr(s, start, j - start);
		if (arr[i] == NULL)
		{
			ft_freeall(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
