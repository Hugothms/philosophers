/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:56:14 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/21 10:54:36 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

# define DIE_EAT_SEMAPHORE "die_eat_semaphore"
# define FORK_SEMAPHORE "fork_semaphore"
# define OUTPUT_SEMAPHORE "output_semaphore"
# define DEATH_SEMAPHORE "death_semaphore"

typedef int	t_msec;

typedef enum e_message
{
	TOOK_FORK,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD
}	t_message;

struct		s_data;
typedef struct s_philo
{
	pthread_t		tid;
	int				philo_number;
	int				number_of_meal;
	t_msec			time_last_meal_started;
	bool			is_dead;
	sem_t			*is_dead_or_eating;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philos;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	int				number_must_eat;
	t_philo			*philos;
	sem_t			*fork;
	sem_t			*output;
	t_msec			simulation_start;
}	t_data;

int		exit_error(const char *str, t_data *data);
bool	check_args(int argc, char **argv);
bool	init_data(t_data *data, int argc, char **argv);
t_msec	get_time(t_data *data);
t_msec	get_total_time(void);
void	ft_putnbr_fd(int n, int fd);
void	release_forks(t_data *data);
void	take_forks(int philo_number, t_data *data);
void	display_message(t_data *data, int philo_number,
			t_message message_type);
void	monitor(t_data *data);
void	free_data(t_data *data);

#endif
