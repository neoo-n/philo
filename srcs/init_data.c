/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:16:31 by dvauthey          #+#    #+#             */
/*   Updated: 2025/04/04 15:16:31 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	init_ac(t_data *data, int *values)
{
	data->nb_philo = values[0];
	data->die = values[1];
	data->eat = values[2];
	data->sleep = values[3];
	data->done_eat = 0;
	data->dead = 0;
	data->end = 0;
}

static int	init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->death, NULL) == -1)
		return (print_err("Mutex not init"), 1);
	if (pthread_mutex_init(&data->print, NULL) == -1)
		return (print_err("Mutex not init"),
			pthread_mutex_destroy(&data->death), 1);
	if (pthread_mutex_init(&data->m_done_eat, NULL) == -1)
		return (print_err("Mutex not init"),
			pthread_mutex_destroy(&data->death),
			pthread_mutex_destroy(&data->print), 1);
	if (pthread_mutex_init(&data->m_last_eat, NULL) == -1)
		return (print_err("Mutex not init"),
			pthread_mutex_destroy(&data->death),
			pthread_mutex_destroy(&data->print),
			pthread_mutex_destroy(&data->m_done_eat), 1);
	if (pthread_mutex_init(&data->end_meal, NULL) == -1)
		return (print_err("Mutex not init"),
			pthread_mutex_destroy(&data->death),
			pthread_mutex_destroy(&data->print),
			pthread_mutex_destroy(&data->m_done_eat),
			pthread_mutex_destroy(&data->m_last_eat), 1);
	return (0);
}

int	init_data(t_data *data, int *values, pthread_mutex_t **fork)
{
	int	i;

	i = 0;
	data->time = time_ms();
	data->philo = init_philo(values, fork, data->time);
	if (!*data->philo)
		return (1);
	init_ac(data, values);
	if (init_data_mutex(data))
		return (clean_data(data, fork), 1);
	while (i < values[0])
	{
		(data->philo[i])->done_eat = &data->done_eat;
		(data->philo[i])->dead = &data->dead;
		(data->philo[i])->end = &data->end;
		(data->philo[i])->death = &data->death;
		(data->philo[i])->end_meal = &data->end_meal;
		(data->philo[i])->print = &data->print;
		(data->philo[i])->m_done_eat = &data->m_done_eat;
		(data->philo[i])->m_last_eat = &data->m_last_eat;
		i++;
	}
	return (0);
}
