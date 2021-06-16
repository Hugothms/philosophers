/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:56:10 by hthomas           #+#    #+#             */
/*   Updated: 2021/06/16 15:11:30 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_data *data, int philo_number, t_message message_type)
{
	pthread_mutex_lock(&data->output);
	if (message_type == TOOK_FORK)
		printf("%d\t%s%d %s%s",
			get_time(data), CYAN, philo_number + 1, "has taken a fork\n", NC);
	else if (message_type == IS_EATING)
		printf("%d\t%s%d %s%s",
			get_time(data), GREEN, philo_number + 1, "is eating\n", NC);
	else if (message_type == IS_SLEEPING)
		printf("%d\t%s%d %s%s",
			get_time(data), YELLOW, philo_number + 1, "is sleeping\n", NC);
	else if (message_type == IS_THINKING)
		printf("%d\t%s%d %s%s",
			get_time(data), ORANGE, philo_number + 1, "is thinking\n", NC);
	else if (message_type == IS_DEAD)
		printf("%d\t%s%d %s%s", get_time(data), RED, philo_number + 1, "died\n", NC);
	if (message_type != IS_DEAD)
		pthread_mutex_unlock(&data->output);
}
