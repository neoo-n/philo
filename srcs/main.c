/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:36 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/30 16:25:39 by dvauthey         ###   ########.fr       */
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

static void	destroy_mutex(t_philo **data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_destroy(data[i]->m_lfork))
			return (print_err("Mutex not destroyed"));
		if (pthread_mutex_destroy(data[i]->m_rfork))
			return (print_err("Mutex not destroyed"));
		i++;
	}
}

int	main(int ac, char **av)
{
	int				values[4];
	int				i;
	t_philo			*data;
	int				*forks;
	pthread_mutex_t	*mutex;

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
	mutex = NULL;
	data = init_data(values, &forks, &mutex);
	if (!data)
		return (free(forks), 1);
	if (philo(data))
		return (free(data), destroy_mutex(&data, values[0]), 1);
	return (0);
}
