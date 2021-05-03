/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:56:14 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/03 12:23:44 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philo_two_H
# define philo_two_H

# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

# define OK 1
# define KO 0
typedef enum e_message
{
	TOOK_FORK,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD
}	t_message;

struct	s_data;

typedef int t_msec;

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
	sem_t			*write_access;
	long			simulation_start;
}	t_data;

int		exit_error(const char *str);
int		check_args(int argc, char **argv);
int		init_data(t_data *data, int argc, char **argv);
t_msec	get_time(t_data *data);
t_msec	get_total_time(void);
void	ft_putnbr_fd(int n, int fd);
void	release_forks(t_data *data);
void	take_forks(int philo_number, t_data *data);
void	display_message(t_data *data, int philo_number, t_message message_type);
void	monitor(t_data *data);
void	free_data(t_data *data);

#endif
