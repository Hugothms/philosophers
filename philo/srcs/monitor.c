/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:25:17 by hthomas           #+#    #+#             */
/*   Updated: 2021/06/09 07:50:14 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philo(t_philo *philo)
{
	if (philo->data->time_to_die
		< get_time(philo->data) - philo->time_last_meal_started)
	{
		display_message(philo->data, philo->philo_number, IS_DEAD);
		philo->is_dead = true;
		pthread_mutex_lock(&philo->is_dead_or_eating);
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
			if (data->philos[i].number_of_meal != data->number_must_eat)
				break ;
			i++;
		}
		if (i == data->number_of_philos)
			return ;
		i = 0;
		while (i < data->number_of_philos)
		{
			if (data->number_must_eat == 0
				|| data->philos[i].number_of_meal != data->number_must_eat)
				if (!check_philo(&data->philos[i]))
					return ;
			i++;
		}
	}
}
