/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:25:17 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/18 12:05:36 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

bool	check_philo(t_philo *philo)
{
	// sem_wait(philo->data->output);
	// printf("time last meal %d: %d\n", philo->philo_number, philo->time_last_meal_started);
	// sem_post(philo->data->output);
	if (philo->data->time_to_die < get_time(philo->data) - philo->time_last_meal_started)
		{
			display_message(philo->data, philo->philo_number, IS_DEAD);
			sem_post(philo->data->death);
			sem_post(philo->is_dead_or_eating);
			return (false);
		}
	return (true);
}

void	monitor(t_data *data)
{
	int	i;

	while (1)
	{
		usleep(1000);
		i = 0;
		while (data->number_must_eat != 0 && i < data->number_of_philos)
		{
			if (data->philo->number_of_meal != data->number_must_eat)
				break ;
			i++;
		}
		if (i == data->number_of_philos)
			return ;
		i = 0;
		while (i < data->number_of_philos)
		{
			if (data->number_must_eat == 0
				|| data->philo->number_of_meal != data->number_must_eat)
				if (!check_philo(data->philo))
					return ;
			i++;
		}
	}
}
