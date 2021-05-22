/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:25:17 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/22 16:18:45 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

bool	check_philo(t_philo *philo)
{
	if (philo->data->time_to_die
		< get_time(philo->data) - philo->time_last_meal_started)
	{
		display_message(philo->data, philo->philo_number, IS_DEAD);
		sem_post(philo->data->death);
		return (false);
	}
	return (true);
}

void	*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		check_philo(philo);
		usleep(1000);
	}
	return (0);
}
