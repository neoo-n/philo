/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                        :+:      :+:    :+:   */
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

static void	init_values(t_philo *philo, int *values, int i, long long time)
{

	philo->nb_philo = values[0];
	philo->die = values[1];
	philo->eat = values[2];
	philo->sleep = values[3];
	philo->last_eat = 0;
	if (values[4])
		philo->nb_eat_tot = values[4];
	else
		philo->nb_eat_tot = -1;
	philo->count_eat = 0;
	philo->time = time;
	philo->philo_id = i + 1;
}

static t_philo	**init_philo(int *values, pthread_mutex_t **fork, long long time)
{
	int				i;
	t_philo			**philo;

	i = 0;
	philo = ft_calloc(values[0], sizeof(t_philo *));
	if (!philo)
		return (NULL);
	*fork = init_mutex(values[0]);
	if (!*fork)
		return (free(philo), NULL);
	while (i < values[0])
	{
		philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!philo[i])
			return (0);
		init_values(philo[i], values, i, time);
		if (i == 0)
			philo[i]->m_lfork = &(*fork)[philo[i]->nb_philo - 1];
		else
			philo[i]->m_lfork = &(*fork)[i - 1];
		philo[i]->m_rfork = &(*fork)[i];
		i++;
	}
	return (philo);
}

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

int	init_data(t_data *data, int *values, pthread_mutex_t **fork)
{
	int	i;

	i = 0;
	data->time = time_ms();
	data->philo = init_philo(values, fork, data->time);
	if (!*data->philo)
		return (1);
	init_ac(data, values);
	if (pthread_mutex_init(&data->death, NULL) == -1
		|| pthread_mutex_init(&data->print, NULL) == -1
		|| pthread_mutex_init(&data->m_done_eat, NULL) == -1
		|| pthread_mutex_init(&data->m_last_eat, NULL) == -1
		|| pthread_mutex_init(&data->end_meal, NULL) == -1)
		return (print_err("Mutex not init"), 1);
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
