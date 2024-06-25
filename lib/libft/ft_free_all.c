/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:01:39 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 13:58:33 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_all(int nb_elem, ...)
{
	va_list	elem;
	void	*to_free;
	int		i;

	i = 0;
	if (nb_elem <= 0)
		return (EXIT_FAILURE);
	va_start(elem, nb_elem);
	while (i < nb_elem)
	{
		to_free = va_arg(elem, void *);
		if (to_free)
		{
			free(to_free);
			to_free = NULL;
		}
		i++;
	}
	va_end(elem);
	return (EXIT_SUCCESS);
}
