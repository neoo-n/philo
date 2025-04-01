/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:56 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/29 19:44:58 by dvauthey         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"


void	ft_sleep(t_philo *philo)
{
	print_actions(philo, "is sleeping");
	ft_usleep(philo->sleep);
}

void	ft_eat(t_philo *philo)
{
	printf("fork : %p\n", philo->m_lfork);
	pthread_mutex_lock(philo->m_lfork);
	print_actions(philo, "has taken a fork");
	if (philo->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->m_lfork);
		ft_usleep(philo->die + 1);
		return ;
	}
	pthread_mutex_lock(philo->m_rfork);
	print_actions(philo, "has taken a fork");
	print_actions(philo, "is eating");
	philo->last_eat = time_ms();
	ft_usleep(philo->eat);
	if (philo->nb_eat_tot > -1)
	{
		philo->count_eat++;
		pthread_mutex_lock(philo->m_eat);
		if (philo->count_eat == philo->nb_eat_tot)
			(*philo->done_eat)++;
		pthread_mutex_unlock(philo->m_eat);
		pthread_mutex_lock(philo->death);
		pthread_mutex_unlock(philo->death);
	}
	pthread_mutex_unlock(philo->m_lfork);
	pthread_mutex_unlock(philo->m_rfork);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (*(philo->dead))
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	return (0);
}
