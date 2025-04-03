/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:56 by dvauthey          #+#    #+#             */
/*   Updated: 2025/04/03 15:15:08 by dvauthey         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"


void	ft_sleep(t_philo *philo)
{
	print_actions(philo, "is sleeping", 0);
	ft_usleep(philo->sleep);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->m_lfork);
	print_actions(philo, "has taken a fork", 0);
	if (philo->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->m_lfork);
		ft_usleep(philo->die);
		return ;
	}
	pthread_mutex_lock(philo->m_rfork);
	print_actions(philo, "has taken a fork", 0);
	print_actions(philo, "is eating", 0);
	pthread_mutex_lock(philo->m_last_eat);
	philo->last_eat = time_ms() - philo->time;
	pthread_mutex_unlock(philo->m_last_eat);
	pthread_mutex_lock(philo->m_done_eat);
	if (philo->nb_eat_tot > -1)
	{
		philo->count_eat++;
		if (philo->count_eat == philo->nb_eat_tot)
			(*(philo->done_eat))++;
	}
	pthread_mutex_unlock(philo->m_done_eat);
	ft_usleep(philo->eat);
	pthread_mutex_unlock(philo->m_lfork);
	pthread_mutex_unlock(philo->m_rfork);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	pthread_mutex_lock(philo->end_meal);
	if (*(philo->end) == 1)
	{
		pthread_mutex_unlock(philo->end_meal);
		return (1);
	}
	pthread_mutex_unlock(philo->end_meal);
	return (0);
}
