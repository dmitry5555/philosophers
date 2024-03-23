/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:53:08 by dlariono          #+#    #+#             */
/*   Updated: 2023/08/08 15:13:25 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	take_forks(t_philo *philo)
{
	int		i;
	int		left_fork_first;
	ssize_t	fork;

	i = 0;
	left_fork_first = philo->position % 2;
	while (i < 2)
	{
		if (is_dead(philo))
			return (1);
		if ((left_fork_first && i == 0) || (!left_fork_first && i == 1))
			fork = philo->r_fork;
		else
			fork = philo->l_fork;
		pthread_mutex_lock(&philo->shared->frks_mutexes[fork]);
		if (!philo->shared->forks[fork])
		{
			ft_msg(philo, get_time(), "TAKING FORK 🥄");
			philo->shared->forks[fork] = 1;
			i++;
		}
		pthread_mutex_unlock(&philo->shared->frks_mutexes[fork]);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	philo->eating = 1;
	philo->start_meal = get_time();
	ft_msg(philo, philo->start_meal, "EATING 🍰");
	ft_usleep(philo->shared->tteat);
	philo->threshold = philo->start_meal + philo->shared->ttdie;
	philo->eating = 0;
	philo->meals += 1;
	if (0 < philo->shared->meals && philo->shared->meals <= philo->meals)
	{
		ft_msg(philo, get_time(), "FINISHED MEALS ✅");
		pthread_mutex_lock(&philo->shared->frks_mutexes[philo->l_fork]);
		philo->shared->forks[philo->l_fork] = 0;
		pthread_mutex_unlock(&philo->shared->frks_mutexes[philo->l_fork]);
		pthread_mutex_lock(&philo->shared->frks_mutexes[philo->r_fork]);
		philo->shared->forks[philo->r_fork] = 0;
		pthread_mutex_unlock(&philo->shared->frks_mutexes[philo->r_fork]);
		philo->shared->finished++;
		if (philo->shared->amount <= philo->shared->finished)
		{
			pthread_mutex_lock(&philo->shared->write_mutex);
			pthread_mutex_unlock(&philo->shared->die_mutex);
			return (1);
		}
	}
	return (0);
}

int	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->frks_mutexes[philo->l_fork]);
	philo->shared->forks[philo->l_fork] = 0;
	pthread_mutex_unlock(&philo->shared->frks_mutexes[philo->l_fork]);
	pthread_mutex_lock(&philo->shared->frks_mutexes[philo->r_fork]);
	philo->shared->forks[philo->r_fork] = 0;
	pthread_mutex_unlock(&philo->shared->frks_mutexes[philo->r_fork]);
	ft_msg(philo, get_time(), "SLEEPING 🛌");
	ft_usleep(philo->shared->ttsleep);
	if (is_dead(philo))
		return (1);
	return (0);
}

void	*routine(void	*curr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)curr_philo;
	philo->start_meal = get_time();
	philo->threshold = philo->start_meal + philo->shared->ttdie;
	while (1)
	{
		if (take_forks(philo) || eat(philo) || release_forks(philo))
			break ;
	}
	return (0);
}
