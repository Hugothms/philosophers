/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:53:40 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/03 10:19:10 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*s_c;

	s_c = (char *)s;
	i = 0;
	while (i < n)
	{
		*(s_c + i) = 0;
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
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	result *= sign;
	return (result);
}

int	init_data(t_data *data, int argc, char **argv)
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
	sem_unlink("fork_semaphore");
	data->fork = sem_open("fork_semaphore", O_CREAT, 0644, data->number_of_philos);
	if (!data->fork)
		return (KO);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (data->philos == NULL)
		return (KO);
	i = 0;
	while (i < data->number_of_philos)
	{
		ft_bzero(&data->philos[i], sizeof(t_philo));
		data->philos[i].data = data;
		sem_unlink("die_or_eat_semaphore");
		data->philos[i].is_dead_or_eating = sem_open("die_or_eat_semaphore", O_CREAT, 0644, 1);
		if (!data->philos[i].is_dead_or_eating)
			return (KO);
		i++;
	}
	sem_unlink("write_semaphore");
	data->write_access = sem_open("write_semaphore", O_CREAT, 0644, 1);
	if (!data->write_access)
		return (KO);
	data->simulation_start = get_total_time();
	return (OK);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		sem_close(data->fork);
		sem_close(data->philos[i].is_dead_or_eating);
		i++;
	}
	free(data->philos);
}
