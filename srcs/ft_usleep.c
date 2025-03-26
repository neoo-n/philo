/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:43:39 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/26 14:23:09 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static long long	time_ms(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000);
}

void	ft_usleep(long long waittime)
{
	long long		start;
	long long		now;

	start = time_ms();
	usleep(waittime * 1000 * 0.75);
	now = time_ms();
	while ((now - start) < waittime)
	{
		usleep(50);
		now = time_ms();
	}
}