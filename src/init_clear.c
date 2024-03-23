/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:54:05 by dlariono          #+#    #+#             */
/*   Updated: 2023/08/08 18:24:09 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_args(t_main *shared, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("WRONG ARG NUM 🛑\n");
		return (1);
	}
	shared->amount = ft_atoi(av[1]);
	shared->ttdie = ft_atoi(av[2]);
	shared->tteat = ft_atoi(av[3]);
	shared->ttsleep = ft_atoi(av[4]);
	if (ac == 6)
		shared->meals = ft_atoi(av[5]);
	if (shared->amount < 1 || shared->ttdie < 1 || shared->tteat < 1
		|| shared->ttsleep < 1 || shared->meals < 1 || shared->amount > 200
		|| shared->ttdie > 2147483647 || shared->ttsleep > 2147483647
		|| shared->meals < 1)
	{
		printf("WRONG ARGS 🛑\n");
		return (1);
	}
	if (ac != 6)
		shared->meals = -1;
	shared->finished = 0;
	return (0);
}

int	init_philos(t_main *shared)
{
	size_t	i;

	shared->philos = malloc(sizeof(t_philo) * shared->amount);
	shared->forks = malloc(sizeof(int) * shared->amount);
	if (!shared->philos || !shared->forks)
		return (1);
	i = 0;
	while (i < shared->amount)
	{
		shared->forks[i] = 0;
		shared->philos[i].position = i;
		shared->philos[i].l_fork = i;
		shared->philos[i].r_fork = (i + 1) % shared->amount;
		shared->philos[i].meals = 0;
		shared->philos[i].eating = 0;
		shared->philos[i].shared = shared;
		i++;
	}
	return (0);
}

int	init_mutexes(t_main *shared)
{
	size_t	i;

	shared->frks_mutexes = malloc(sizeof(pthread_mutex_t) * shared->amount);
	if (!shared->frks_mutexes)
		return (1);
	i = 0;
	while (i < shared->amount)
	{
		pthread_mutex_init(&shared->frks_mutexes[i], NULL);
		i++;
	}
	pthread_mutex_init(&shared->write_mutex, NULL);
	pthread_mutex_init(&shared->die_mutex, NULL);
	return (0);
}

int	clear(t_main *shared)
{
	size_t	i;

	i = 0;
	while (i < shared->amount)
	{
		pthread_mutex_destroy(&shared->frks_mutexes[i]);
		i++;
	}
	pthread_mutex_destroy(&shared->write_mutex);
	pthread_mutex_destroy(&shared->die_mutex);
	free(shared->frks_mutexes);
	free(shared->philos);
	free(shared->forks);
	return (0);
}
