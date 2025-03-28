/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:26 by marvin            #+#    #+#             */
/*   Updated: 2025/03/28 14:45:31 by marvin           ###   ########.fr       */
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
	data->forks[data->philo_id - 1] = 1;
	printf("%lli %i has taken a right fork\n", time_ms(), data->philo_id);
	if (data->philo_id == 1)
		data->forks[data->nb_philo - 1] = 1;
	else
		data->forks[data->philo_id - 2] = 1;
	printf("%lli %i has taken a left fork\n", time_ms(), data->philo_id);
}
