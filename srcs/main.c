/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:44:36 by dvauthey          #+#    #+#             */
/*   Updated: 2025/04/04 14:53:09 by dvauthey         ###   ########.fr       */
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

static int	is_num(char **av)
{
	int	i;
	int	j;

	j = 1;
	while (av[j])
	{
		i = 0;
		if (av[j][i] == '-' || av[j][i] == '+')
			i++;
		while (av[j][i])
		{
			if (av[j][i] < '0' || av[j][i] > '9')
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

static int	*init_val(char **av, int ac)
{
	int	*values;
	int	i;

	i = 0;
	if (!is_num(av))
		return (printf("Error : arguments not numbers\n"), NULL);
	values = ft_calloc(ac, sizeof(int));
	if (!values)
		return (NULL);
	values[0] = ft_atoi(av[1]);
	values[1] = ft_atoi(av[2]);
	values[2] = ft_atoi(av[3]);
	values[3] = ft_atoi(av[4]);
	if (ac == 6)
		values[4] = ft_atoi(av[5]);
	while (i < ac - 1)
	{
		if (values[i] <= 0)
		{
			return (printf("Error : numerical arguments not valid\n"),
				free(values), NULL);
		}
		i++;
	}
	return (values);
}

int	main(int ac, char **av)
{
	int				*values;
	t_data			data;
	pthread_mutex_t	*fork;

	if (ac_error(ac))
		return (1);
	values = init_val(av, ac);
	if (!values)
		return (1);
	if (init_data(&data, values, &fork))
		return (free(values), 1);
	free(values);
	if (ft_philo(&data))
		return (clean_data(&data, &fork), 1);
	clean_data(&data, &fork);
	return (0);
}
