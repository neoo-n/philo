/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:36 by dvauthey          #+#    #+#             */
/*   Updated: 2025/04/01 16:28:19 by dvauthey         ###   ########.fr       */
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
		write(2, "Too many arguments\n", 19);
		return (1);
	}
	return (0);
}

static int	*init_val(char **av, int ac)
{
	int	*values;

	values = ft_calloc(ac, sizeof(int));
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

// static void	destroy_mutex(t_philo **philo, int nb)
// {
// 	int	i;

// 	i = 0;
// 	while (i < nb)
// 	{
// 		if (pthread_mutex_destroy(philo[i]->m_lfork))
// 			return (print_err("Mutex not destroyed"));
// 		if (pthread_mutex_destroy(philo[i]->m_rfork))
// 			return (print_err("Mutex not destroyed"));
// 		i++;
// 	}
// }

int	main(int ac, char **av)
{
	int				*values;
	t_data			data;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*shared;

	if (ac_error(ac))
		return (1);
	if (ft_atoi(av[1]) == 0)
		return (0);
	values = init_val(av, ac);
	if (!values)
		return (1);
	if (init_data(&data, &shared, values, &fork))
		return (free(values), 1);
	free(values);
	if (ft_philo(&data))
		return (1);
	return (0);
}
