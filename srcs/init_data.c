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

static void	init_values(t_philo *data, int *values, int i)
{
	data->nb_philo = values[0];
	data->die = values[1];
	data->eat = values[2];
	data->sleep = values[3];
	data->philo_id = i + 1;
}

static void	init_forks(t_philo *data, int i, int **forks)
{
	data->forks = forks;
	if (i == 0)
		data->lfork_id = data->nb_philo - 1;
	else
		data->lfork_id = i - 1;
	data->rfork_id = i;
	
}

t_philo	*init_data(int *values, int **forks, pthread_mutex_t **mutex)
{
	int				i;
	t_philo			*data;

	i = 0;
	data = ft_calloc(values[0], sizeof(t_philo));
	if (!data)
		return (NULL);
	*mutex = init_mutex(values[0]);
	if (!(*mutex))
		return (free(data), NULL);
	while (i < values[0])
	{
		init_values(&data[i], values, i);
		init_forks(&data[i], i, forks);
		if (i == 0)
			data->m_lfork = mutex[data->nb_philo - 1];
		else
			data->m_lfork = mutex[i - 1];
		data->m_rfork = mutex[i];
		i++;
	}
	return (data);
}
