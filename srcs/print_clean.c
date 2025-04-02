/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:27 by dvauthey          #+#    #+#             */
/*   Updated: 2025/04/02 12:25:51 by dvauthey         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

void	print_actions(t_philo *philo, char *s, int dying)
{
	pthread_mutex_lock(philo->print);
	if (dying == 0)
	{
		pthread_mutex_lock(philo->death);
		if (*(philo->dead) == 1)
		{
			// printf("after time code : %lli %i\n", time_ms() - philo->time, philo->philo_id);
			pthread_mutex_unlock(philo->death);
			pthread_mutex_unlock(philo->print);
			return ;
		}
		pthread_mutex_unlock(philo->death);
	}
	printf("%lli %i", time_ms() - philo->time, philo->philo_id);
	printf(" %s\n", s);
	pthread_mutex_unlock(philo->print);
}
