/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:31:23 by hthomas           #+#    #+#             */
/*   Updated: 2021/04/30 12:44:46 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long	get_total_time(void)
{
	struct timeval	tv;
	long			total_time;

	gettimeofday(&tv, NULL);
	total_time = ((long)tv.tv_sec * 1000) + ((long)tv.tv_usec / 1000);
	return (total_time);
}

int	get_time(t_data *data)
{
	return ((int)(get_total_time() - data->simulation_start));
}
