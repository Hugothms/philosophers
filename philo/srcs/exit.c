/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:29:00 by hthomas           #+#    #+#             */
/*   Updated: 2021/06/09 07:50:14 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_error(const char *str, t_data *data)
{
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
	if (data)
		free_data(data);
	return (1);
}
