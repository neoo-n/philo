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
	t_philo	data;

	data = *(t_philo *)arg;
	pthread_mutex_lock(&data.mutex);
	printf("i : %i\n", data.philo_id);
	pthread_mutex_unlock(&data.mutex);
	return (arg);
}

int	philo(int *value)
{
	t_philo			*data;
	pthread_t		*philo;
	int				i;

	i = 0;
	data = ft_calloc(value[0], sizeof(t_philo));
	if (!data)
		return (free(value), 1);
	philo = ft_calloc(value[0], sizeof(pthread_t *));
	if (!philo)
		return (free(data), free(value), 1);
	while (i < value[0])
	{
		pthread_mutex_init(&data[i].mutex, NULL);
		data[i].philo_id = i;
		if (pthread_create(&philo[data[i].philo_id], NULL, &routine, &data[i]))
			write(2, "Error : thread not created\n", 27);
		i++;
	}
	i = 0;
	while (i < value[0])
	{
		if (pthread_join(philo[i], NULL))
			write(2, "Error : Thread not joined\n", 26);
		i++;
	}
	free(philo);
	i = 0;
	while (i < value[0])
	{
		pthread_mutex_destroy(&data[i].mutex);
		i++;
	}
	return (0);
}
