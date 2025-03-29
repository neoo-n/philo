/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:27 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/29 19:44:30 by dvauthey         ###   ########.fr       */
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