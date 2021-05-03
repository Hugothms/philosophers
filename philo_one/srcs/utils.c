/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:53:40 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/03 10:21:15 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (data->philos == NULL)
		return (KO);
	i = 0;
	while (i < data->number_of_philos)
	{
		ft_bzero(&data->philos[i], sizeof(t_philo));
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].fork, NULL);
		pthread_mutex_init(&data->philos[i].is_dead_or_eating, NULL);
		i++;
	}
	pthread_mutex_init(&data->write_access, NULL);
	data->simulation_start = get_total_time();
	return (1);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].fork);
		pthread_mutex_destroy(&data->philos[i].is_dead_or_eating);
		i++;
	}
	free(data->philos);
}
