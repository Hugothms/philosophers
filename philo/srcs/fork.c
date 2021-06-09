/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:08:58 by hthomas           #+#    #+#             */
/*   Updated: 2021/06/09 07:50:14 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(int philo_number, t_data *data)
{
	pthread_mutex_lock(&data->philos[philo_number - 1].fork);
	display_message(data, philo_number, TOOK_FORK);
	if (philo_number - 1 == data->number_of_philos - 1)
		pthread_mutex_lock(&data->philos[0].fork);
	else
		pthread_mutex_lock(&data->philos[philo_number - 1 + 1].fork);
	display_message(data, philo_number, TOOK_FORK);
}

void	release_forks(int philo_number, t_data *data)
{
	pthread_mutex_unlock(&data->philos[philo_number - 1].fork);
	if (philo_number - 1 == data->number_of_philos - 1)
		pthread_mutex_unlock(&data->philos[0].fork);
	else
		pthread_mutex_unlock(&data->philos[philo_number - 1 + 1].fork);
}
