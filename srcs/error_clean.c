/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:52:57 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/28 11:52:52 by marvin           ###   ########.fr       */
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