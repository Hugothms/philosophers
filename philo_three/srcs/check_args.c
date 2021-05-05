/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 20:06:55 by hthomas           #+#    #+#             */
/*   Updated: 2021/05/04 18:32:40 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static bool	is_number(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str++ > '9')
			return (false);
	}
	return (true);
}

bool	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (false);
		i++;
	}
	return (true);
}
