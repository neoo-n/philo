/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:05 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/29 19:54:42 by dvauthey         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

static int	init_mutex(pthread_mutex_t **mutex, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(mutex[i], NULL) == -1)
			return (print_err("Mutex not init"), 1);
		i++;
	}
	return (0);
}

static void	init_forks(t_philo *data, pthread_mutex_t **mutex, int i,
	int **forks)
{
	data->forks = forks;
	if (i == 0)
	{
		data->m_lfork = mutex[data->nb_philo - 1];
		data->lfork_id = data->nb_philo - 1;
	}
	else
	{
		data->m_lfork = mutex[i - 1];
		data->lfork_id = i - 1;
	}
	data->m_rfork = mutex[i];
	data->rfork_id = i;
}

t_philo	*init_data(pthread_mutex_t **mutex, int *values, int **forks)
{
	int		i;
	t_philo	*data;

	i = 0;
	if (init_mutex(mutex, values[0]))
		return (free(values), NULL);
	data = ft_calloc(values[0], sizeof(t_philo));
	if (!data)
		return (free(values), NULL);
	while (i < values[0])
	{
		data[i].nb_philo = values[0];
		data[i].die = values[1];
		data[i].eat = values[2];
		data[i].sleep = values[3];
		data[i].philo_id = i + 1;
		init_forks(&data[i], mutex, i, forks);
		i++;
	}
	return (free(values), data);
}
