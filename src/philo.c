/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:43:53 by dlariono          #+#    #+#             */
/*   Updated: 2023/08/08 19:46:56 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_dead(t_philo *philo)
{
	if (!philo->eating && get_time() > philo->threshold)
	{
		ft_msg(philo, get_time(), "DIED ❌");
		pthread_mutex_lock(&philo->shared->write_mutex);
		pthread_mutex_unlock(&philo->shared->die_mutex);
		return (1);
	}
	return (0);
}

int	run_threads(t_main *shared)
{
	size_t		i;
	pthread_t	tid;

	i = 0;
	pthread_mutex_lock(&shared->die_mutex);
	while (i < shared->amount)
	{
		if (pthread_create(&tid, NULL, &routine, (void *)&shared->philos[i]))
			return (printf("thread error\n"));
		pthread_detach(tid);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_main	shared;

	if (init_args(&shared, ac, av))
		return (0);
	init_philos(&shared);
	init_mutexes(&shared);
	if (run_threads(&shared))
		return (1);
	// pthread_mutex_lock(&shared.die_mutex);
	// pthread_mutex_unlock(&shared.die_mutex);
	clear(&shared);
	exit(0);
}
