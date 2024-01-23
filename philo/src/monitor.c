/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:59:00 by alajara-          #+#    #+#             */
/*   Updated: 2021/11/04 22:17:00 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_monitor(t_params *par, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < par->num && philo)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	pthread_mutex_destroy(par->over_mtx);
	pthread_mutex_destroy(par->meal_mtx);
	pthread_mutex_destroy(par->fork);
	pthread_mutex_destroy(par->ready_mtx);
	free(par->over_mtx);
	free(par->meal_mtx);
	free(par->fork);
	free(par->ready_mtx);
	free(philo);
}

int	monitoring(t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * params->num);
	if (!philo || init_philo(params, philo))
		return (EXIT_FAILURE);
	if (init_monitor(params, philo))
		return (EXIT_FAILURE);
	check_monitor(params, philo);
	end_monitor(params, philo);
	return (0);
}
