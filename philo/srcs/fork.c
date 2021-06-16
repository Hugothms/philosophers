/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:08:58 by hthomas           #+#    #+#             */
/*   Updated: 2021/06/16 17:51:57 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(int philo_number, t_data *data)
{
	// printf("  %d\n", philo_number + 1);
	if (data->philos)
	{
		pthread_mutex_lock(&data->philos[philo_number].fork);
		// printf("\t%d took fork %d (1)\n", philo_number + 1, philo_number + 1);
		if (data->philos)
			display_message(data, philo_number, TOOK_FORK);
	}
	if (data->philos)
	{
		if (philo_number == data->number_of_philos - 1)
		{
			pthread_mutex_lock(&data->philos[0].fork);
			// printf("\t%d took fork %d (2)\n", philo_number + 1, 1);
		}
		else
		{
			pthread_mutex_lock(&data->philos[philo_number + 1].fork);
			// printf("\t%d took fork %d (3)\n", philo_number + 1, philo_number + 1 + 1);
		}
		if (data->philos)
			display_message(data, philo_number, TOOK_FORK);
	}
}

void	release_forks(int philo_number, t_data *data)
{
	if (data->philos)
		pthread_mutex_unlock(&data->philos[philo_number].fork);
	if (data->philos)
	{
		if (philo_number == data->number_of_philos - 1)
			pthread_mutex_unlock(&data->philos[0].fork);
		else if (data)
			pthread_mutex_unlock(&data->philos[philo_number + 1].fork);
	}
}
