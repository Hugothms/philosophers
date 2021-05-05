/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:56:10 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/04 09:33:40 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	display_message(t_data *data, int philo_number, t_message message_type)
{
	sem_wait(data->output);
	if (message_type == TOOK_FORK)
		printf("%d\t%d %s",
			get_time(data), philo_number, "has taken a fork\n");
	else if (message_type == IS_EATING)
		printf("%d\t%d %s",
			get_time(data), philo_number, "is eating\n");
	else if (message_type == IS_SLEEPING)
		printf("%d\t%d %s",
			get_time(data), philo_number, "is sleeping\n");
	else if (message_type == IS_THINKING)
		printf("%d\t%d %s",
			get_time(data), philo_number, "is thinking\n");
	else if (message_type == IS_DEAD)
		printf("%d\t%d %s", get_time(data), philo_number, "died\n");
	if (message_type != IS_DEAD)
		sem_post(data->output);
}
