/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:16:42 by dvauthey          #+#    #+#             */
/*   Updated: 2025/04/04 15:21:29 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	dying(t_data *data, int i)
{
	pthread_mutex_lock(&data->m_last_eat);
	if (time_ms() - data->time - data->philo[i]->last_eat >= data->die)
	{
		pthread_mutex_unlock(&data->m_last_eat);
		pthread_mutex_lock(&data->death);
		data->dead = 1;
		pthread_mutex_unlock(&data->death);
		print_actions(data->philo[i], "died", 1);
		return (1);
	}
	pthread_mutex_unlock(&data->m_last_eat);
	return (0);
}

static int	mealing(t_data *data)
{
	pthread_mutex_lock(&data->m_done_eat);
	if (data->done_eat == data->nb_philo)
	{
		pthread_mutex_unlock(&data->m_done_eat);
		pthread_mutex_lock(&data->end_meal);
		data->end = 1;
		pthread_mutex_unlock(&data->end_meal);
		return (1);
	}
	pthread_mutex_unlock(&data->m_done_eat);
	return (0);
}

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
			end = dying(data, i);
			if (end)
				break ;
			end = mealing(data);
			if (end)
				break ;
			i++;
		}
		if (end == 1)
			break ;
	}
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(philo->m_last_eat);
	philo->last_eat = time_ms() - philo->time;
	pthread_mutex_unlock(philo->m_last_eat);
	while (!is_dead(philo))
	{
		if (is_dead(philo))
			break ;
		print_actions(philo, "is thinking", 0);
		if (is_dead(philo))
			break ;
		ft_eat(philo);
		if (is_dead(philo))
			break ;
		ft_sleep(philo);
	}
	return (arg);
}

int	ft_philo(t_data *data)
{
	pthread_t	*th_philo;
	pthread_t	end;
	int			i;

	i = -1;
	th_philo = ft_calloc(data->philo[0]->nb_philo, sizeof(pthread_t *));
	if (!th_philo)
		return (1);
	if (pthread_create(&end, NULL, &ft_end, data))
		return (print_err("Thread not created"), 1);
	while (++i < data->nb_philo)
	{
		if (pthread_create(&th_philo[i], NULL, &routine, data->philo[i]))
			return (print_err("Thread not created"), free(th_philo), 1);
	}
	i = -1;
	if (pthread_join(end, NULL))
		return (print_err("Thread not joined"), free(th_philo), 1);
	while (++i < data->philo[0]->nb_philo)
	{
		if (pthread_join(th_philo[i], NULL))
			return (print_err("Thread not joined"), free(th_philo), 1);
	}
	return (free(th_philo), 0);
}
