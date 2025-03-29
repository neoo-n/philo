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
	printf("%lli %i is sleeping\n", time_ms(), data->philo_id);
	ft_usleep(data->sleep);
}

void	ft_eat(t_philo *data)
{
	(*data->forks)[data->rfork_id] = 1;
	printf("%lli %i has taken a right fork\n", time_ms(), data->philo_id);
	(*data->forks)[data->lfork_id] = 1;
	printf("%lli %i has taken a left fork\n", time_ms(), data->philo_id);
	printf("%lli %i is eating\n", time_ms(), data->philo_id);
	ft_usleep(data->eat);
	(*data->forks)[data->rfork_id] = 0;
	(*data->forks)[data->lfork_id] = 0;
}
