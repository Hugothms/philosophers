/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:56:14 by hthomas           #+#    #+#             */
/*   Updated: 2021/04/30 12:30:17 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

typedef enum e_message
{
	TOOK_FORK,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD
}	t_message;

struct	s_data;

typedef struct s_philo
{
	pthread_t		tid;
	int				philo_number;
	int				number_of_meal;
	int				time_last_meal_started;
	int				is_dead;
	pthread_mutex_t	fork;
	pthread_mutex_t	is_dead_or_eating;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	t_philo			*philos;
	pthread_mutex_t	write_access;
	long			simulation_start;
}	t_data;

int		exit_error(const char *str);
int		check_args(int argc, char **argv);
int		init_data(t_data *data, int argc, char **argv);
int		get_time(t_data *data);
long	get_total_time(void);
void	ft_putnbr_fd(int n, int fd);
void	release_forks(int philo_number, t_data *data);
void	take_forks(int philo_number, t_data *data);
void	display_message(t_data *data, int philo_number, t_message message_type);
void	monitor(t_data *data);
void	free_data(t_data *data);

#endif
