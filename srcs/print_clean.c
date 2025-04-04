/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:27 by dvauthey          #+#    #+#             */
/*   Updated: 2025/04/04 15:01:05 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_data(t_data *data, pthread_mutex_t **forks)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		free(data->philo[i]);
		pthread_mutex_destroy(&(*forks)[i]);
		i++;
	}
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->end_meal);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->m_done_eat);
	pthread_mutex_destroy(&data->m_last_eat);
	if (forks)
		free(*forks);
	free(data->philo);
}

void	free_philo(t_philo **philo, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (philo[i])
			free(philo[i]);
		i++;
	}
	free(philo);
}

void	print_err(char *s)
{
	write(2, "Error : ", 8);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

void	print_actions(t_philo *philo, char *s, int dying)
{
	pthread_mutex_lock(philo->print);
	if (dying == 0)
	{
		pthread_mutex_lock(philo->death);
		if (*(philo->dead) == 1)
		{
			pthread_mutex_unlock(philo->death);
			pthread_mutex_unlock(philo->print);
			return ;
		}
		pthread_mutex_unlock(philo->death);
	}
	pthread_mutex_lock(philo->end_meal);
	if (*(philo->end) == 1)
	{
		pthread_mutex_unlock(philo->end_meal);
		pthread_mutex_unlock(philo->print);
		return ;
	}
	pthread_mutex_unlock(philo->end_meal);
	printf("%lli %i", time_ms() - philo->time, philo->philo_id);
	printf(" %s\n", s);
	pthread_mutex_unlock(philo->print);
}
