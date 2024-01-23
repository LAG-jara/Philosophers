/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:59:00 by alajara-          #+#    #+#             */
/*   Updated: 2021/11/04 22:17:00 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->par->meal_mtx);
	if (philo->par->check_meal)
	{
		if (philo->iter_num >= philo->par->max_iter)
			++philo->par->philos_full;
		if (philo->par->philos_full == philo->par->num)
			return (pthread_mutex_unlock(philo->par->meal_mtx) || 1);
	}
	pthread_mutex_unlock(philo->par->meal_mtx);	
	return (0);
}

static int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(philo->par->over_mtx);
	philo->dead = 1;
	print_routine(philo, DIE);
	philo->par->over = 1;
	pthread_mutex_unlock(philo->par->over_mtx);
	pthread_mutex_unlock(philo->rf);
	return (1);
}

// check if someones needs to die.
static int	check_death(t_philo *philo)
{
	long int	now;

	pthread_mutex_lock(philo->par->meal_mtx);
	now = time_now() - philo->meal;
	pthread_mutex_unlock(philo->par->meal_mtx);
	if (now >= philo->par->t2d)
		return (someone_died(philo));
	return (0);
}

void	check_monitor(t_params *par, t_philo *philo)
{
	int	i;

	while (!par->over)
	{
		i = -1;
		par->philos_full = 0;
		while (++i < par->num)
		{
			if (check_death(&philo[i]) || \
				check_meals(&philo[i]))
			{
				pthread_mutex_lock(par->over_mtx);
				par->over = 1;
				pthread_mutex_unlock(par->over_mtx);
			}
		}
		usleep(30);
	}
	if (par->check_meal && !pthread_mutex_lock(philo->par->meal_mtx) && \
	philo[par->num - 1].iter_num >= par->max_iter)
	{
		ft_usleep(100);
		printf("\n\tAll philosophers have eaten %d times\n", par->max_iter);
		pthread_mutex_unlock(philo->par->meal_mtx);
		return (final_print(1));
	}
	pthread_mutex_unlock(philo->par->meal_mtx);
	return (final_print(0));
}
