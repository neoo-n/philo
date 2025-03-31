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

static void	*ft_end(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	while (1)
	{
		if (time_ms() - data->last_eat >= data->die)
		{
			pthread_mutex_lock(data->death);
			*(data->dead) = 1;
			pthread_mutex_unlock(data->death);
			print_actions(data, "died");
			break ;
		}
		pthread_mutex_lock(data->m_eat);
		if (*data->done_eat == data->nb_philo)
		{

		}
	}
	return (NULL);
}

static void *routine(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	if (data->philo_id % 2 == 0)
		ft_usleep(1);
	data->last_eat = time_ms();
	while (!is_dead(data))
	{
		ft_eat(data);
		ft_sleep(data);
		print_actions(data, "is thinking");
	}
	return (arg);
}

int	philo(t_philo *data)
{
	pthread_t		*philo;
	pthread_t		end;
	int				i;

	i = 0;
	philo = ft_calloc(data[0].nb_philo, sizeof(pthread_t *));
	if (!philo)
		return (1);
	if (pthread_create(&end, NULL, &ft_end, &data[i]))
		return (print_err("Thread not created"), cleanup(philo), 1);
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
