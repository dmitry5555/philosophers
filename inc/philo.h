/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:43:33 by dlariono          #+#    #+#             */
/*   Updated: 2023/08/08 15:07:16 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	size_t			position;
	size_t			l_fork;
	size_t			r_fork;
	size_t			meals;
	size_t			eating;
	size_t			start_meal;
	size_t			threshold;
	struct s_main	*shared;
}	t_philo;

typedef struct s_main
{
	size_t			amount;
	size_t			tteat;
	size_t			ttdie;
	size_t			ttsleep;
	size_t			meals;
	size_t			finished;
	t_philo			*philos;
	int				*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*frks_mutexes;
	pthread_mutex_t	die_mutex;
}	t_main;

int		ft_atoi(char *str);
size_t	get_time(void);
void	ft_usleep(size_t ms);
void	ft_msg(t_philo *philo, size_t timestamp, char *msg);
int		init_args(t_main *shared, int ac, char **av);
int		init_philos(t_main *shared);
int		init_mutexes(t_main *shared);
int		is_dead(t_philo *philo);
int		take_forks(t_philo *philo);
int		eat(t_philo *philo);
int		release_forks(t_philo *philo);
void	*routine(void	*curr_philo);
int		run_threads(t_main *shared);
int		clear(t_main *shared);

#endif