/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:59:00 by alajara-          #+#    #+#             */
/*   Updated: 2021/11/04 22:17:00 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Only executes if are 4 or 5 arguments and 
// if the parameters are properly initialitated.
int	main(int ac, char **ag)
{
	t_params	p;

	if (ac != 5 && ac != 6)
		return (error_msg("Error: invalid arguments\n", 0, 0, 0));
	if (init_params(&p, ac, ag))
	{
		end_monitor(&p, NULL);
		return (EXIT_FAILURE);
	}
	if (monitoring(&p))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
