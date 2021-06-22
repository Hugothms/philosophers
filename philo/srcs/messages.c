/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:56:10 by hthomas           #+#    #+#             */
/*   Updated: 2021/06/22 16:49:11 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_data *data, int philo_n, t_message message_type)
{
	pthread_mutex_lock(&data->output);
	if (!data->is_dead)
	{
		if (message_type == TOOK_FORK)
			printf("%d\t%s%d %s%s",
				get_time(data), CYAN, philo_n + 1, "has taken a fork\n", NC);
		else if (message_type == IS_EATING)
			printf("%d\t%s%d %s%s",
				get_time(data), GREEN, philo_n + 1, "is eating\n", NC);
		else if (message_type == IS_SLEEPING)
			printf("%d\t%s%d %s%s",
				get_time(data), YELLOW, philo_n + 1, "is sleeping\n", NC);
		else if (message_type == IS_THINKING)
			printf("%d\t%s%d %s%s",
				get_time(data), ORANGE, philo_n + 1, "is thinking\n", NC);
	}
	if (message_type == IS_DEAD)
		printf("%d\t%s%d %s%s", get_time(data), RED, philo_n + 1, "died\n", NC);
	pthread_mutex_unlock(&data->output);
}
