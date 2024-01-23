/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:59:00 by alajara-          #+#    #+#             */
/*   Updated: 2021/11/04 22:17:00 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_routine_mutex(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->par->over_mtx);
	print_routine(philo, action);
	pthread_mutex_unlock(philo->par->over_mtx);
}

// The cool part of this project and where the magic happen.
static void	ft_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->lf);
	print_routine_mutex(philo, LFORK);
	pthread_mutex_lock(philo->rf);
	print_routine_mutex(philo, RFORK);
	pthread_mutex_lock(philo->par->meal_mtx);
	philo->meal = time_now();
	philo->iter_num++;
	pthread_mutex_unlock(philo->par->meal_mtx);
	print_routine_mutex(philo, EAT);
	ft_usleep(philo->par->t2e);
	print_routine_mutex(philo, SLEEP);
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
	ft_usleep(philo->par->t2s);
	print_routine_mutex(philo, THINK);
}

// 
void	*philo_routine(void *job)
{
	t_philo	*philo;

	philo = (t_philo *)job;
	while (!pthread_mutex_lock(philo->par->ready_mtx) && !philo->par->ready
		&& !pthread_mutex_unlock(philo->par->ready_mtx))
		usleep(50);
	pthread_mutex_unlock(philo->par->ready_mtx);
	if (philo->id & 1)
		ft_usleep(philo->par->t2e * 0.9 + 1);
	while (!pthread_mutex_lock(philo->par->over_mtx) && !philo->par->over)
	{
		pthread_mutex_unlock(philo->par->over_mtx);
		ft_routine(philo);
	}
	pthread_mutex_unlock(philo->par->over_mtx);
	return (NULL);
}
