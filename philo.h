/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:02:57 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/28 14:05:59 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

// STRUCT
typedef struct	s_philo
{
	int				philo_id;
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				*forks;
	pthread_mutex_t	*mutex;
}				t_philo;


// FUNCTIONS
int			philo(t_philo *data);

// utils
long long	time_ms(void);
void		ft_usleep(long long waittime);
int			ft_atoi(const char *str);
void 	   *ft_calloc(size_t count, size_t size);
int			ft_strlen(char *s);

// cleanup and error
void		cleanup(pthread_t *philo);
void		print_err(char *s);

#endif