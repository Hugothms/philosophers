/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:08:58 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/03 10:33:38 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	take_forks(int philo_number, t_data *data)
{
	sem_wait(data->fork);
	display_message(data, philo_number, TOOK_FORK);
	sem_wait(data->fork);
	display_message(data, philo_number, TOOK_FORK);
}

void	release_forks(t_data *data)
{
	sem_post(data->fork);
	sem_post(data->fork);
}
