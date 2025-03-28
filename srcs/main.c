/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:36 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/29 19:59:13 by dvauthey         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

static int	ac_error(int ac)
{
	if (ac != 5)
	{
		if (ac > 5)
			write(2, "Too many arguments\n", 19);
		if (ac < 5)
			write(2, "Too few arguments\n", 18);
		return (1);
	}
	return (0);
}

static void	destroy_mutex(pthread_mutex_t **mutex, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_destroy(mutex[i]))
			return (print_err("Mutex not destroyed"));
		i++;
	}
}

int	main(int ac, char **av)
{
	int				values[4];
	int				i;
	t_philo			*data;
	pthread_mutex_t	*mutex;
	int				*forks;

	if (ac_error(ac))
		return (1);
	i = 0;
	while (i < 4)
	{
		values[i] = ft_atoi(av[i + 1]);
		i++;
	}
	forks = ft_calloc(values[0], sizeof(int));
	if (!forks)
		return (1);
	data = init_data(&mutex, values, &forks);
	if (!data)
		return (1);
	if (philo(data))
		return (free(data), destroy_mutex(&mutex, values[0]), 1);
	return (0);
}
