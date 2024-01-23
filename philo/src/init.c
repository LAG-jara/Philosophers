/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:59:00 by alajara-          #+#    #+#             */
/*   Updated: 2021/11/04 22:17:00 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_params *par, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < par->num)
	{
		philo[i].id = i;
		philo[i].dead = 0;
		philo[i].iter_num = 0;
		philo[i].monitor_start = 0;
		philo[i].meal = 0;
		philo[i].par = par;
		philo[i].lf = &par->fork[i];
		philo[i].rf = 0;
	}
	return (0);
}

static int	mutex_alloc(t_params *par)
{
	par->meal_mtx = malloc(sizeof(pthread_mutex_t));
	if (!par->meal_mtx)
		return (error_msg("Error\nMutex meal: malloc failed\n", par, 0, 1));
	par->ready_mtx = malloc(sizeof(pthread_mutex_t));
	if (!par->ready_mtx)
		return (error_msg("Error\nMutex ready: malloc failed\n", par, 0, 1));
	par->over_mtx = malloc(sizeof(pthread_mutex_t));
	if (!par->over_mtx)
		return (error_msg("Error\nMutex over: malloc failed\n", par, 0, 1));
	par->fork = malloc(sizeof(pthread_mutex_t) * par->num);
	if (!par->fork)
		return (error_msg("Error\nMutex fork: malloc failed\n", par, 0, 1));
	return (0);
}

static int	init_params_mutex(t_params *par)
{
	int	i;

	par->over_mtx = 0;
	par->fork = 0;
	if (mutex_alloc(par))
		return (1);
	if (pthread_mutex_init(par->meal_mtx, NULL) == -1)
		return (error_msg("Error\nMutex meal failed\n", par, 0, 1));
	if (pthread_mutex_init(par->over_mtx, NULL) == -1)
		return (error_msg("Error\nMutex init failed\n", par, 0, 1));
	i = -1;
	if (pthread_mutex_init(par->ready_mtx, NULL) == -1)
		return (error_msg("Error\nMutex init failed\n", par, 0, 1));
	i = -1;
	while (++i < par->num)
		if (pthread_mutex_init(&par->fork[i], NULL) == -1)
			return (error_msg("Error\nMutex init failed\n", par, 0, 1));
	return (0);
}

// Sets up the parameters in par depending the args ac and av. 
int	init_params(t_params *par, int ac, char **av)
{
	int	mutex;

	mutex = -1;
	par->num = ft_atoi(av[1]);
	par->t2d = ft_atoi(av[2]);
	par->t2e = ft_atoi(av[3]);
	par->t2s = ft_atoi(av[4]);
	par->max_iter = -2;
	par->check_meal = 0;
	par->philos_full = 0;
	par->start = 0;
	par->ready = 0;
	if (ac == 6)
	{
		par->check_meal = 1;
		par->max_iter = ft_atoi(av[5]);
		if (par->max_iter < 1)
			par->max_iter = 0;
	}
	par->over = 0;
	if (par->num > 0)
		mutex = init_params_mutex(par);
	return (mutex || par->num <= 0 || par->t2d <= 0 || par->t2e <= 0
		|| par->t2s <= 0 || par->max_iter == 0);
}

int	init_monitor(t_params *par, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < par->num)
	{
		philo[i].rf = philo[(i + 1) % par->num].lf;
		if (pthread_create(&philo[i].life_tid, NULL, &philo_routine,
				&philo[i]) == -1)
			return (error_msg("Error\nFail createing thread\n", par, philo, 2));
	}
	i = -1;
	par->start = time_now();
	while (++i < par->num)
	{
		philo[i].monitor_start = par->start;
		pthread_mutex_lock(par->meal_mtx);
		philo[i].meal = par->start;
		pthread_mutex_unlock(par->meal_mtx);
	}
	pthread_mutex_lock(par->ready_mtx);
	par->ready = 1;
	pthread_mutex_unlock(par->ready_mtx);
	return (0);
}
