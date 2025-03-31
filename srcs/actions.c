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


void	ft_sleep(t_philo *data)
{
	print_actions(data, "is sleeping");
	ft_usleep(data->sleep);
}

void	ft_eat(t_philo *data)
{
	pthread_mutex_lock(data->m_lfork);
	print_actions(data, "has taken a fork");
	if (data->nb_philo == 1)
	{
		pthread_mutex_unlock(data->m_lfork);
		ft_usleep(data->die);
		return ;
	}
	pthread_mutex_lock(data->m_rfork);
	print_actions(data, "has taken a fork");
	print_actions(data, "is eating");
	data->last_eat = time_ms();
	ft_usleep(data->eat);
	if (data->nb_eat_tot > -1)
	{
		data->count_eat++;
		if (data->count_eat == data->nb_eat_tot)
			(*data->done_eat)++;
		pthread_mutex_lock(data->death);
		pthread_mutex_unlock(data->death);
	}
	pthread_mutex_unlock(data->m_lfork);
	pthread_mutex_unlock(data->m_rfork);
}

int	is_dead(t_philo *data)
{
	pthread_mutex_lock(data->death);
	if (*(data->dead))
	{
		printf("maybe\n");
		pthread_mutex_unlock(data->death);
		return (1);
	}
	pthread_mutex_unlock(data->death);
	return (0);
}
