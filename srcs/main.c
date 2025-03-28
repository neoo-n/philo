/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:01:05 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/28 12:01:52 by marvin           ###   ########.fr       */
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

static t_philo	*init_data(char **av)
{
	int		i;
	int		value[4];
	t_philo	*data;

	i = 0;
	value[0] = ft_atoi(av[1]);
	value[1] = ft_atoi(av[2]);
	value[2] = ft_atoi(av[3]);
	value[3] = ft_atoi(av[4]);
	data = ft_calloc(value[0], sizeof(t_philo));
	if (!data)
		return (NULL);
	while (i < value[0])
	{
		data[i].nb_philo = value[0];
		data[i].die = value[1];
		data[i].eat = value[2];
		data[i].sleep = value[3];
		i++;
	}
	return (data);
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
	data = init_data(av);
	if (!data)
		return (1);
	error_philo = philo(data);
	if (data)
		free(data);
	if (error_philo)
		return (1);
	return (0);
}
