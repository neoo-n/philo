/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:02:57 by dvauthey          #+#    #+#             */
/*   Updated: 2025/04/03 15:11:36 by dvauthey         ###   ########.fr       */
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
	long long		time;
	long long		die;
	long long		eat;
	long long		sleep;
	long long		last_eat;
	int				nb_eat_tot;
	int				count_eat;
	int				*done_eat;
	int				*dead;
	int				*end;
	pthread_mutex_t	*m_lfork;
	pthread_mutex_t	*m_rfork;
	pthread_mutex_t	*death;
	pthread_mutex_t	*end_meal;
	pthread_mutex_t	*print;
	pthread_mutex_t	*m_done_eat;
	pthread_mutex_t	*m_last_eat;

}				t_philo;

typedef struct	s_data
{
	t_philo			**philo;
	int				nb_philo;
	long long		time;
	long long		die;
	long long		eat;
	long long		sleep;
	int				done_eat;
	int				dead;
	int				end;
	pthread_mutex_t	death;
	pthread_mutex_t	end_meal;
	pthread_mutex_t	print;
	pthread_mutex_t	m_done_eat;
	pthread_mutex_t	m_last_eat;
}				t_data;


// FUNCTIONS
int			init_data(t_data *data, int *values, pthread_mutex_t **fork);
int			ft_philo(t_data *data);
void		ft_sleep(t_philo *philo);
void		ft_eat(t_philo *data);
int			is_dead(t_philo *philo);

// utils
long long	time_ms(void);
void		ft_usleep(long long waittime);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
int			ft_strlen(char *s);
void		init_var(int *a, int *b, int *c, int *d);

// clean and print
void		cleanup(pthread_t *philo);
void		print_err(char *s);
void		print_actions(t_philo *philo, char *s, int dying);

#endif