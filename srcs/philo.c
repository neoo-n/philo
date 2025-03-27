/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:09:21 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/26 16:27:46by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void *routine(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	while (1)
	{
		ft_sleep;
	}
	return (arg);
}

int	philo(int *value, t_philo *data)
{
	pthread_t		*philo;
	// pthread_mutex_t	mutex;
	int				i;
	// int				*fork;

	i = 0;
	philo = ft_calloc(value[0], sizeof(pthread_t *));
	if (!philo)
		return (1);
	// fork = ft_calloc(value[0], sizeof(int));
	// if (!fork)
	// 	return (free(philo), 1);
	// if (pthread_mutex_init(&mutex, NULL) == -1)
	// 	return (print_err("Mutex not init"), cleanup(philo), 1);
	while (i < value[0])
	{
		data[i].philo_id = i;
		// data[i].mutex = &mutex;
		// data[i].fork = &fork;
		if (pthread_create(&philo[i], NULL, &routine, &data[i]))
			return (print_err("Thread not created"), cleanup(philo), 1);
		i++;
	}
	i = 0;
	while (i < value[0])
	{
		if (pthread_join(philo[i], NULL))
			return (print_err("Thread not joined"), cleanup(philo), 1);
		i++;
	}
	// if (pthread_mutex_destroy(&mutex))
	// 	return (print_err("Mutex not destroyed"), cleanup(philo), 1);
	cleanup (philo);
	return (0);
}
