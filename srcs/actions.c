/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:26 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 15:37:59 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"


void	ft_sleep(t_philo *data, char *s)
{
	printf("%lli %i ", time_ms(), data->philo_id);
	write(1, s, ft_strlen(s));
	ft_usleep(data.)
}