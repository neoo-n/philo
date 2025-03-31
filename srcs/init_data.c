/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:05 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/30 16:25:52 by dvauthey         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

static pthread_mutex_t	*init_mutex(int nb)
{
	pthread_mutex_t	*mutex;
	int	i;

	i = 0;
	mutex = ft_calloc(nb, sizeof(pthread_mutex_t));
	if (!mutex)
		return (NULL);
	while (i < nb)
	{
		if (pthread_mutex_init(&mutex[i], NULL) == -1)
			return (print_err("Mutex not init"), free(mutex), NULL);
		i++;
	}
	return (mutex);
}

static void	init_values(t_philo *data, int *values, int i, long long time)
{
	int	done_eat;
	int	dead;

	done_eat = 0;
	dead = 0;
	data->nb_philo = values[0];
	data->die = values[1];
	data->eat = values[2];
	data->sleep = values[3];
	data->last_eat = 0;
	if (values[4])
		data->nb_eat_tot = values[4];
	else
		data->nb_eat_tot = -1;
	data->count_eat = 0;
	data->time = time;
	data->philo_id = i + 1;
	data->done_eat = &done_eat;
	data->dead = &dead;
}

int	init_data(t_philo **data, int *values, pthread_mutex_t **fork)
{
	int				i;
	long long		time;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	m_eat;

	i = 0;
	*fork = init_mutex(values[0]);
	if (!*fork)
		return (1);
	if (pthread_mutex_init(&death, NULL))
		return (print_err("Mutex not init"), free(fork), 1);
	if (pthread_mutex_init(&print, NULL))
		return (print_err("Mutex not init"), free(fork), 1);
	if (pthread_mutex_init(&m_eat, NULL))
		return (print_err("Mutex not init"), free(fork), 1);
	time = time_ms();
	while (i < values[0])
	{
		init_values(data[i], values, i, time);
		(*data)[i].death = &death;
		(*data)[i].print = &print;
		(*data)[i].m_eat = &m_eat;
		if (i == 0)
			(*data)[i].m_lfork = &(*fork)[(*data)[i].nb_philo - 1];
		else
			(*data)[i].m_lfork = &(*fork)[i - 1];
		(*data)[i].m_rfork = &(*fork)[i];
		i++;
	}
	return (0);
}
