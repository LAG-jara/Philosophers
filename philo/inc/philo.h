/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:32:05 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/13 17:58:05 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define LFORK "has taken left fork"
# define RFORK "has taken right fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\e[0;31mDIED\e[m"
# define LEFT 0
# define RIGHT 1

/*
					num			= number of philos
					ready		= is ready to start the race 
					t2d			= time to die
					t2e			= time to eat
					t2s			= time to sleep
					max_iter	= maximum times needed to eat
					check_meal	= is a limited number of runs
					over		= is the race over (?) 1 yes, 2 dead, 3 eaten
					start		= time where the everything is ready
					death		= is anyone dead?
					fork		= any fork not ready (?)
*/
typedef struct s_params
{
	int				num;
	int				ready;
	int				t2d;
	int				t2e;
	int				t2s;
	int				max_iter;
	int				check_meal;
	int				philos_full;
	int				over;
	long int		start;
	pthread_mutex_t	*meal_mtx;
	pthread_mutex_t	*ready_mtx;
	pthread_mutex_t	*over_mtx;
	pthread_mutex_t	*fork;
}	t_params;

/*
					id				= identification/index
					dead			= is dead
					iter_num		= number of iterations
					monitor_start	= 
					meal			= meals eaten
					life_tid		= life thread id
					lf				= left fork
					rf				= right fork
					par				= parameters
*/
typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long int		monitor_start;
	long int		meal;
	pthread_t		life_tid;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	t_params		*par;
}	t_philo;

// Inits
int			init_params(t_params *par, int ac, char **av);
int			init_monitor(t_params *par, t_philo *philo);
int			init_philo(t_params *p, t_philo *philo);
int			ft_atoi(const char *str);
//Utils
void		end_monitor(t_params *par, t_philo *philo);
int			error_msg(char *s, t_params *par, t_philo *p, int malloc);
void		*philo_routine(void *job);
void		final_print(int alive);
int			monitoring(t_params *p);
void		check_monitor(t_params *par, t_philo *philo);
void		print_routine(t_philo *p, char *action);
// Time
int			ft_usleep(long int time);
long int	time_now(void);

#endif