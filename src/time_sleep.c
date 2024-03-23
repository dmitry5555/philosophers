/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sleep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:52:24 by dlariono          #+#    #+#             */
/*   Updated: 2023/08/08 19:15:39 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}

size_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t ms)
{
	size_t	end;

	end = get_time() + ms;
	while (get_time() < end)
		ft_usleep(ms / 1000);
}

void	ft_msg(t_philo *philo, size_t timestamp, char *msg)
{
	pthread_mutex_lock(&philo->shared->write_mutex);
	printf("%zu %zu %s\n", timestamp, philo->position, msg);
	pthread_mutex_unlock(&philo->shared->write_mutex);
}
