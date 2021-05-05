/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:29:00 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/04 18:10:53 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	exit_error(const char *str, t_data *data)
{
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
	if (data)
	{
		if (data->philo)
			free(data->philo);
		if (data->pids)
			free(data->pids);
	}
	return (1);
}
