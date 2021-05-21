/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:53:40 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/21 11:27:39 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	sem_unlink(FORK_SEMAPHORE);
	data->fork = sem_open(FORK_SEMAPHORE, O_CREAT, 0644, data->number_of_philos);
	if (!data->fork)
		return (false);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (data->philos == NULL)
		return (false);
	i = 0;
	while (i < data->number_of_philos)
	{
		ft_bzero(&data->philos[i], sizeof(t_philo));
		data->philos[i].data = data;
		sem_unlink(DIE_EAT_SEMAPHORE);
		data->philos[i].is_dead_or_eating = sem_open(DIE_EAT_SEMAPHORE, O_CREAT, 0644, 1);
		if (!data->philos[i].is_dead_or_eating)
			return (false);
		i++;
	}
	sem_unlink(OUTPUT_SEMAPHORE);
	data->output = sem_open(OUTPUT_SEMAPHORE, O_CREAT, 0644, 1);
	if (!data->output)
		return (false);
	data->simulation_start = get_total_time();
	return (true);
}

void	free_data(t_data *data)
{
	int	i;

	if (data->output)
		sem_close(data->output);
	if (data->fork)
		sem_close(data->fork);
	if (data->philos)
	{
		i = 0;
		while (i < data->number_of_philos)
			sem_close(data->philos[i++].is_dead_or_eating);
		free(data->philos);
	}
}
