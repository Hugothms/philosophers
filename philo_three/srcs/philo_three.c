/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:41:07 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/24 07:32:27 by hthomas          ###   ########.fr       */
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

static void	philo_sleep(t_philo *philo, int philo_number)
{
	int	time_to_end_sleeping;

	display_message(philo->data, philo_number, IS_SLEEPING);
	time_to_end_sleeping = get_time(philo->data) + philo->data->time_to_sleep;
	while (get_time(philo->data) < time_to_end_sleeping)
	{
		check_philo(philo);
		usleep(10);
	}
}

static void	*philo(t_philo *philo)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, &monitor, philo) != 0)
		return (NULL);
	pthread_detach(tid);
	while (1)
	{
		philo_eat(philo->data, philo->philo_number);
		if (philo->data->number_must_eat != 0
			&& philo->number_of_meal == philo->data->number_must_eat)
		{
			sem_post(philo->data->death);
			printf("philo %d ate enough\n", philo->philo_number);
			return (NULL);
		}
		philo_sleep(philo, philo->philo_number);
		display_message(philo->data, philo->philo_number, IS_THINKING);
	}
	printf("philo %d MMMMMMMMMMMMMMMM\n", philo->philo_number);
}

static bool	start_philos(t_data *data, int count)
{
	data->pids[count] = fork();
	if (data->pids[count] == -1)
		return (false);
	else if (data->pids[count] == 0)
	{
		data->philo->philo_number = data->number_of_philos - count;
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

void	*monitor_eat_enough(void *data_v)
{
	t_data	*data;
	int		i;

	data = data_v;
	i = 0;
	while(i < data->number_of_philos)
	{
		sem_wait(data->eat_enough);
		printf("monitor_eat_enough %d\n", i);
		i++;
	}
	sem_post(data->death);
	printf("DONE monitor_eat_enough\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	pthread_t	tid;

	if (argc < 5)
		return (exit_error("Error: missing argument(s).\n", NULL));
	if (argc > 6)
		return (exit_error("Error: too much arguments.\n", NULL));
	if (!check_args(argc, argv))
		return (exit_error("Error: invalid arguments.\n", NULL));
	if (!init_data(&data, argc, argv))
		return (exit_error("Error: cannot allocate memory.", &data));
	if (!start_philos(&data, data.number_of_philos - 1))
		return (exit_error("Error: cannot start threads.\n", &data));
	printf("main ===========%d\n", data.number_of_philos);
	if (pthread_create(&tid, NULL, &monitor_eat_enough, &data) != 0)
		return (1);
	// pthread_detach(tid);
	sem_wait(data.death);
	// usleep(10000);
	free_data(&data);
	pthread_kill(tid, 0);
	return (0);
}
