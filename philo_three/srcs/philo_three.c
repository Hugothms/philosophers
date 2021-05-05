/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:41:07 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/04 18:48:02 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	philo_eat(t_data *data, int philo_number)
{
	int	time_to_end_eating;

	take_forks(philo_number, data);
	display_message(data, philo_number, IS_EATING);
	data->philo->number_of_meal++;
	data->philo->time_last_meal_started = get_time(data);
	time_to_end_eating = data->philo->time_last_meal_started
		+ data->time_to_eat;
	sem_wait(data->philo->is_dead_or_eating);
	while (get_time(data) < time_to_end_eating)
		usleep(10);
	sem_post(data->philo->is_dead_or_eating);
	release_forks(data);
}

static void	philo_sleep(t_data *data, int philo_number)
{
	int	time_to_end_sleeping;

	display_message(data, philo_number, IS_SLEEPING);
	time_to_end_sleeping = get_time(data) + data->time_to_sleep;
	while (get_time(data) < time_to_end_sleeping)
		usleep(10);
}

static void	*philo(t_philo *philo)
{
	while (1)
	{
		philo_eat(philo->data, philo->philo_number);
		if (philo->data->number_must_eat != 0
			&& philo->number_of_meal == philo->data->number_must_eat)
			return (NULL);
		printf("time last meal %d: %d\n", philo->philo_number, philo->time_last_meal_started);
		if (philo->time_last_meal_started + philo->data->time_to_die
		< get_time(philo->data))
		{
			display_message(philo->data, philo->philo_number, IS_DEAD);
			sem_post(philo->data->death);
			sem_post(philo->is_dead_or_eating);
			return (false);
		}
		if (philo->)
			return (NULL);
		philo_sleep(philo->data, philo->philo_number);
		display_message(philo->data, philo->philo_number, IS_THINKING);
	}
}

static bool	start_philos(t_data *data, int count)
{

	data->pids[count] = fork();
	if (data->pids[count] == -1)
		return (false);
	else if (data->pids[count] == 0)
	{
		data->philo->philo_number = count;
		philo(data->philo);
	}
	else if (count > 0)
	{
		if (!start_philos(data, count - 1))
		{
			kill(data->pids[count], SIGTERM);
			return (false);
		}
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
	if (!start_philos(&data, data.number_of_philos))
		return (exit_error("Error: cannot start threads.\n", &data));
	monitor(&data);
	usleep(10000);
	free_data(&data);
	return (0);
}
