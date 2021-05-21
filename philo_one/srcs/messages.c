/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:56:10 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/21 11:49:54 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	display_message(t_data *data, int philo_number, t_message message_type)
{
	pthread_mutex_lock(&data->output);
	if (message_type == TOOK_FORK)
		printf("%d\t%d %s",
			get_time(data), philo_number + 1, "has taken a fork\n");
	else if (message_type == IS_EATING)
		printf("%d\t%d %s",
			get_time(data), philo_number + 1, "is eating\n");
	else if (message_type == IS_SLEEPING)
		printf("%d\t%d %s",
			get_time(data), philo_number + 1, "is sleeping\n");
	else if (message_type == IS_THINKING)
		printf("%d\t%d %s",
			get_time(data), philo_number + 1, "is thinking\n");
	else if (message_type == IS_DEAD)
		printf("%d\t%d %s", get_time(data), philo_number + 1, "died\n");
	if (message_type != IS_DEAD)
		pthread_mutex_unlock(&data->output);
}
