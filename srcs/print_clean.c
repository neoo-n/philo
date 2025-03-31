/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:27 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/31 17:32:56 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup(pthread_t *philo)
{
	if (philo)
		free(philo);
}

void	print_err(char *s)
{
	write(2, "Error : ", 8);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

void	print_actions(t_philo *data, char *s)
{
	pthread_mutex_lock(data->death);
	if (*(data->dead))
	{
		pthread_mutex_unlock(data->death);
		return ;
	}
	pthread_mutex_unlock(data->death);
	pthread_mutex_lock(data->print);
	printf("%lli %i", time_ms() - data->time, data->philo_id);
	printf(" %s\n", s);
	pthread_mutex_unlock(data->print);
}
