/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:31:23 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/03 12:23:56 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

t_msec	get_total_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long)tv.tv_sec * 1000) + ((long)tv.tv_usec / 1000));
}

t_msec	get_time(t_data *data)
{
	return ((get_total_time() - data->simulation_start));
}
