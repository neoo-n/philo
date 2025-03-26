/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:02:57 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/26 16:38:20 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

// struct

typedef struct	s_philo
{
	int				*nb_ph;
	pthread_mutex_t	mutex;
}				t_philo;


// FUNCTIONS
int		philo(int *value);

// utils
void	ft_usleep(long long waittime);
int		ft_atoi(const char *str);
void    *ft_calloc(size_t count, size_t size);


#endif