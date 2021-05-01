/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:08:58 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/01 20:49:56 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	take_forks(int philo_number, t_data *data)
{
	sem_wait(data->fork);
	display_message(data, philo_number, TOOK_FORK);
	if (philo_number == data->number_of_philos - 1)
		sem_wait(data->fork);
	else
		sem_wait(data->fork);
	display_message(data, philo_number, TOOK_FORK);
}

void	release_forks(int philo_number, t_data *data)
{
	sem_post(data->fork);
	if (philo_number == data->number_of_philos - 1)
		sem_post(data->fork);
	else
		sem_post(data->fork);
}
