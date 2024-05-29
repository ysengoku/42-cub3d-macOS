/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:35:53 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/23 10:36:15 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_perror_exit(char *message, int code)
{
	perror(message);
	exit(code);
}

void	ft_error_exit(char *message, int code)
{
	ft_putendl_fd(message, 2);
	exit(code);
}
