/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:41:07 by hthomas           #+#    #+#             */
/*   Updated: 2021/06/22 16:49:19 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_data *data, int philo_number)
{
	int	time_to_end_eating;

	take_forks(philo_number, data);
	display_message(data, philo_number, IS_EATING);
	data->philos[philo_number].number_of_meal++;
	data->philos[philo_number].time_last_meal_started = get_time(data);
	time_to_end_eating = data->philos[philo_number].time_last_meal_started
		+ data->time_to_eat;
	while (data->philos && get_time(data) < time_to_end_eating)
		usleep(10);
	release_forks(philo_number, data);
}

static void	philo_sleep(t_data *data, int philo_number)
{
	int	time_to_end_sleeping;

	display_message(data, philo_number, IS_SLEEPING);
	time_to_end_sleeping = get_time(data) + data->time_to_sleep;
	while (data->philos && get_time(data) < time_to_end_sleeping)
		usleep(10);
}

static void	*philo(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (!philo->data->is_dead)
	{
		philo_eat(philo->data, philo->philo_number);
		if (philo->data->number_must_eat != 0
			&& philo->number_of_meal == philo->data->number_must_eat)
			return (NULL);
		philo_sleep(philo->data, philo->philo_number);
		display_message(philo->data, philo->philo_number, IS_THINKING);
	}
	return (NULL);
}

static bool	start_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].philo_number = i;
		if (pthread_create(&(data->philos[i].tid), NULL, &philo,
				&(data->philos[i])))
			return (false);
		usleep(1000);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5)
		return (exit_error("Error: missing argument(s).\n", NULL));
	if (argc > 6)
		return (exit_error("Error: too much arguments.\n", NULL));
	if (!check_args(argc, argv))
		return (exit_error("Error: invalid arguments.\n", NULL));
	if (!init_data(&data, argc, argv))
		return (exit_error("Error: cannot allocate memory.", &data));
	if (argc == 6 && data.number_must_eat == 0)
	{
		free_data(&data);
		return (0);
	}
	if (!start_philos(&data))
		return (exit_error("Error: cannot start threads.\n", &data));
	monitor(&data);
	usleep(5 * 1000);
	free_data(&data);
	return (0);
}
