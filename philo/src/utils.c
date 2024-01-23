/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:59:00 by alajara-          #+#    #+#             */
/*   Updated: 2021/11/04 22:17:00 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *s, t_params *par, t_philo *philo, int malloc)
{
	if (malloc)
	{
		if (par->meal_mtx)
			free(par->meal_mtx);
		if (par->over_mtx)
			free(par->over_mtx);
		if (par->fork)
			free(par->fork);
		if (par->ready_mtx)
			free(par->ready_mtx);
		if (philo)
			free(philo);
	}
	return (printf("%s", s));
}

void	print_routine(t_philo *philo, char *action)
{
	if (philo->par->over == 1)
		return ;
	printf("%ld ms %d %s\n", time_now() - philo->monitor_start, philo->id + 1,
		action);
}

// When all philos
void	final_print(int alive)
{
	printf("\t/-=-=-=-=-=-=-=-=-=\\\n");
	if (alive)
		printf("\t|  I'M LOVIN' IT®  |\t🍔🍟\n");
	else
		printf("\t|     YOU DIED     |\t💀\n");
	printf("\t\\=-=-=-=-=-=-=-=-=-/\n");
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	--i;
	while (str[++i] >= '0' && str[i] <= '9')
		res = (res * 10) + str[i] - '0';
	return (res * sign);
}
