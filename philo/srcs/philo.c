/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:41:07 by hthomas           #+#    #+#             */
/*   Updated: 2021/06/16 17:57:00 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_data *data, int philo_number)
{
	int	time_to_end_eating;

	// printf("%d wants to eat\n", philo_number + 1);
	take_forks(philo_number, data);
	if (data->philos)
		display_message(data, philo_number, IS_EATING);
	data->philos[philo_number].number_of_meal++;
	data->philos[philo_number].time_last_meal_started = get_time(data);
	time_to_end_eating = data->philos[philo_number].time_last_meal_started
		+ data->time_to_eat;
	while (data->philos && get_time(data) < time_to_end_eating)
		usleep(10);
	// printf("%d is done eating\n", philo_number + 1);
	if (data)
		release_forks(philo_number, data);
	// printf("%d released the forks\n", philo_number + 1);
}

static void	philo_sleep(t_data *data, int philo_number)
{
	int	time_to_end_sleeping;

	if (data->philos)
		display_message(data, philo_number, IS_SLEEPING);
	time_to_end_sleeping = get_time(data) + data->time_to_sleep;
	while (data->philos && get_time(data) < time_to_end_sleeping)
		usleep(10);
}

static void	*philo(void *philo_v)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_v;
	while (1)
	{
		// printf("start routine\n");
		philo_eat(philo->data, philo->philo_number);
		if (philo && philo->data->philos && philo->data->number_must_eat != 0
			&& philo->number_of_meal == philo->data->number_must_eat)
		{
			// printf("%d end eating and number_must_eat reached\n", philo->philo_number + 1);
			return (NULL);
		}
		// printf("ok\n");
		i = 0;
		// printf("%d checks if others are not dead (start)\n", philo->philo_number + 1);
		while (philo && philo->data->philos && i < philo->data->number_of_philos)
		{
			if (philo->data->philos[i].is_dead)
			{
				// printf("%d end eating and someone is_dead\n", philo->philo_number + 1);
				return (NULL);
			}
			i++;
		}
		// printf("ok2\n");
		if (!philo)
			return (NULL);
		// printf("%d wants to sleep\n", philo->philo_number + 1);
		philo_sleep(philo->data, philo->philo_number);
		if (philo && philo->data->philos && philo->data->number_must_eat != 0
			&& philo->number_of_meal == philo->data->number_must_eat)
		{
			// printf("%d end eating and number_must_eat reached\n", philo->philo_number + 1);
			return (NULL);
		}
		i = 0;
		// printf("%d checks if others are not dead (start)\n", philo->philo_number + 1);
		while (philo && philo->data->philos && i < philo->data->number_of_philos)
		{
			if (philo->data->philos[i].is_dead)
			{
				// printf("%d end eating and someone is_dead\n", philo->philo_number + 1);
				return (NULL);
			}
			i++;
		}
		// printf("%d wants to think\n", philo->philo_number + 1);
		if (philo && philo->data->philos)
			display_message(philo->data, philo->philo_number, IS_THINKING);
	}
}

static bool	start_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].philo_number = i;
		// printf("CREATE %d\n", i + 1);
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
	if (!start_philos(&data))
		return (exit_error("Error: cannot start threads.\n", &data));
	// printf("Start monitor\n");
	monitor(&data);
	// usleep(5 * 1000);
	free_data(&data);
	// printf("%sfree_data done%s\n", RED, NC);
	return (0);
}
