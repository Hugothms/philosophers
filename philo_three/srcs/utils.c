/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:53:40 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/20 14:03:29 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		*(str + i) = 0;
		i++;
	}
}

static int	ft_atoi(const char *str)
{
	int		sign;
	int		result;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	return (result * sign);
}

bool	malloc_semaphores(t_data *data)
{
	data->pids = malloc(sizeof(*data->pids) * data->number_of_philos);
	if (!data->pids)
		return (false);
	sem_unlink(FORK_SEMAPHORE);
	data->fork = sem_open(FORK_SEMAPHORE, O_CREAT,
			0644, data->number_of_philos);
	if (!data->fork)
		return (false);
	sem_unlink(OUTPUT_SEMAPHORE);
	data->output = sem_open(OUTPUT_SEMAPHORE, O_CREAT, 0644, 1);
	if (!data->output)
		return (false);
	sem_unlink(DEATH_SEMAPHORE);
	data->death = sem_open(DEATH_SEMAPHORE, O_CREAT, 0644, 0);
	if (!data->death)
		return (false);
	data->simulation_start = get_total_time();
	return (true);
}

bool	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_must_eat = ft_atoi(argv[5]);
	else
		data->number_must_eat = 0;
	data->philo = malloc(sizeof(*data->philo));
	if (data->philo == NULL)
		return (false);
	i = 0;
	while (i++ < data->number_of_philos)
	{
		ft_bzero(data->philo, sizeof(*data->philo));
		data->philo->data = data;
		sem_unlink(DIE_EAT_SEMAPHORE);
		data->philo->is_dead_or_eating = sem_open(DIE_EAT_SEMAPHORE, O_CREAT,
				0644, 1);
		if (!data->philo->is_dead_or_eating)
			return (false);
	}
	return (malloc_semaphores(data));
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		sem_close(data->fork);
		sem_close(data->philo->is_dead_or_eating);
		sem_close(data->output);
		sem_close(data->death);
		i++;
	}
	free(data->philo);
	free(data->pids);
}
