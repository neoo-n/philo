/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:01:05 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/26 16:16:20 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int			*value;

	if (ac != 2)
	{
		ac_error(ac);
		return (1);
	}
	value = NULL;
	value = ft_calloc(1, sizeof(int));
	if (!value)
		return (1);
	init_value(&value, av);
	if (philo(value))
		return (1);
	return (0);
}
