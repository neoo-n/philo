/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:36 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/31 17:40:30 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ac_error(int ac)
{
	if (ac < 5)
	{
		write(2, "Too few arguments\n", 18);
		return (1);
	}
	if (ac > 6)
	{
		write(2, "Too few arguments\n", 18);
		return (1);
	}
	return (0);
}

static int	*init_val(char **av, int ac)
{
	int	*values;

	values = ft_calloc(ac - 1, sizeof(int));
	if (!values)
		return (NULL);
	values[0] = ft_atoi(av[1]);
	values[1] = ft_atoi(av[2]);
	values[2] = ft_atoi(av[3]);
	values[3] = ft_atoi(av[4]);
	if (ac == 6)
		values[4] = ft_atoi(av[5]);
	return (values);
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
	int				*values;
	t_philo			*data;
	pthread_mutex_t	*fork;

	if (ac_error(ac))
		return (1);
	values = init_val(av, ac);
	if (!values)
		return (1);
	if (values[0] == 0)
		return (0);
	data = ft_calloc(values[0], sizeof(t_philo));
	if (!data)
		return (free(values), 1);
	if (init_data(&data, values, &fork))
		return (free(data), free(values), 1);
	free(values);
	if (philo(data))
		return (free(data), destroy_mutex(&data, values[0]), 1);
	return (0);
}
