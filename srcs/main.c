/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:01:05 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/27 15:40:56 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

static void	ac_error(int ac)
{
	if (ac > 2)
		write(2, "Too many arguments\n", 19);
	if (ac < 2)
		write(2, "Too few arguments\n", 18);
}

static void	init_value(int **value, char **av)
{
	*(value[0]) = ft_atoi(av[1]);
	// *(value[1]) = ft_atoi(av[2]);
	// *(value[2]) = ft_atoi(av[3]);
	// *(value[3]) = ft_atoi(av[4]);
}

int	main(int ac, char **av)
{
	int		error_philo;
	t_philo	*data;

	if (ac != 2)
	{
		ac_error(ac);
		return (1);
	}
	data = ft_calloc(ft_atoi(av[1]), sizeof(t_philo));
	if (!data)
		return (1);
	data.values = ft_calloc(1, sizeof(int));
	if (!data.values)
		return (1);
	init_value(&data.values, av);
	error_philo = philo(data);
	if (data.values)
		free(data.values);
	if (data)
		free(data);
	if (error_philo)
		return (1);
	return (0);
}
