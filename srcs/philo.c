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
	int i;

	data = (t_philo *)arg;
	i = 0;
	while (i < 4)
	{
		printf("here : lfork : %i, rfork : %i\n", data->lfork_id, data->rfork_id);
		if (!((*data->forks)[data->lfork_id]) && !((*data->forks)[data->rfork_id]))
		{
			printf("in here\n");
			pthread_mutex_lock(data->m_lfork);
			pthread_mutex_lock(data->m_rfork);
			ft_eat(data);
			pthread_mutex_lock(data->m_lfork);
			pthread_mutex_lock(data->m_rfork);
		}
		ft_sleep(data);
		i++;
	}
	return (arg);
}

int	philo(t_philo *data)
{
	pthread_t		*philo;
	int				i;

	i = 0;
	philo = ft_calloc(data[0].nb_philo, sizeof(pthread_t *));
	if (!philo)
		return (1);
	while (i < data[0].nb_philo)
	{
		if (pthread_create(&philo[i], NULL, &routine, &data[i]))
			return (print_err("Thread not created"), cleanup(philo), 1);
		i++;
	}
	i = 0;
	while (i < data[0].nb_philo)
	{
		if (pthread_join(philo[i], NULL))
			return (print_err("Thread not joined"), cleanup(philo), 1);
		i++;
	}
	cleanup (philo);
	return (0);
}
