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
	t_data	*data;
	int		i;
	int		end;

	data = (t_data *)arg;
	end = 0;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->m_last_eat);
			if (time_ms() - data->time - data->philo[i]->last_eat >= data->die)
			{
				pthread_mutex_unlock(&data->m_last_eat);
				pthread_mutex_lock(&data->death);
				data->dead = 1;
				pthread_mutex_unlock(&data->death);
				print_actions(data->philo[i], "died", 1);
				end = 1;
				break ;
			}
			pthread_mutex_unlock(&data->m_last_eat);
			pthread_mutex_lock(&data->m_done_eat);
			if (data->done_eat == data->nb_philo)
			{
				pthread_mutex_unlock(&data->m_done_eat);
				pthread_mutex_lock(&data->end_meal);
				data->end = 1;
				pthread_mutex_unlock(&data->end_meal);
				end = 1;
				break ;
			}
			pthread_mutex_unlock(&data->m_done_eat);
			i++;
		}
		if (end == 1)
			break ;
	}
	return (NULL);
}

static void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	philo->last_eat = time_ms();
	while (!is_dead(philo))
	{
		if (is_dead(philo))
			break ;
		ft_eat(philo);
		if (is_dead(philo))
			break ;
		ft_sleep(philo);
		if (is_dead(philo))
			break ;
		print_actions(philo, "is thinking", 0);
	}
	return (arg);
}

int	ft_philo(t_data *data)
{
	pthread_t	*th_philo;
	pthread_t	end;
	int			i;

	i = 0;
	th_philo = ft_calloc(data->philo[0]->nb_philo, sizeof(pthread_t *));
	if (!th_philo)
		return (1);
	if (pthread_create(&end, NULL, &ft_end, data))
		return (print_err("Thread not created"), 1);
	while (i < data->nb_philo)
	{
		if (pthread_create(&th_philo[i], NULL, &routine, data->philo[i]))
			return (print_err("Thread not created"), cleanup(th_philo), 1);
		i++;
	}
	i = 0;
	while (i < data->philo[0]->nb_philo)
	{
		if (pthread_join(th_philo[i], NULL))
			return (print_err("Thread not joined"), cleanup(th_philo), 1);
		i++;
	}
	cleanup (th_philo);
	return (0);
}
