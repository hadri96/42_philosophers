/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:50:41 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/12 13:55:45 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		error_exit(FULL_ERROR, data);
		exit(EXIT_FAILURE);
	}
	return (data);
}

bool	check_wrappers(char *str)
{
	if (str[0] == '[' && str[ft_strlen(str) - 1] == ']')
		return (true);
	return (false);
}

int	check_numeric(int ac, char **av, char **times)
{
	if (ac == 6)
	{
		if (check_wrappers(av[5]) && ft_strlen(av[5]) > 2)
			*times = ft_substr(av[5], 1, ft_strlen(av[5]) - 2);
		else
			*times = NULL;
		if (!(*times))
			return (1);
		if (!ft_strisdigit(av[1]) || !ft_strisdigit(av[2])
			|| !ft_strisdigit(av[3]) || !ft_strisdigit(av[4])
			|| !ft_strisdigit(*times))
		{
			free(*times);
			return (1);
		}
	}
	else
	{
		if (!ft_strisdigit(av[1]) || !ft_strisdigit(av[2])
			|| !ft_strisdigit(av[3]) || !ft_strisdigit(av[4]))
			return (1);
	}
	return (0);
}

int	parse_input(int ac, char **av, t_data *d)
{
	char	*times;

	if (check_numeric(ac, av, &times))
		return (error_exit(NON_NUMERIC, d), 1);
	d->n_philos = ft_atol(av[1]);
	d->time_to_die = ft_atol(av[2]);
	d->time_to_eat = ft_atol(av[3]);
	d->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
	{
		d->limit_meals = ft_atol(times);
		free(times);
	}
	else
		d->limit_meals = -1;
	if (d->time_to_die < 1 || d->time_to_eat < 1 || d->time_to_sleep < 1
		|| (ac == 6 && d->limit_meals < 1) || d->n_philos > INT_MAX
		|| d->time_to_die > INT_MAX || d->time_to_eat > INT_MAX
		|| d->time_to_sleep > INT_MAX || d->limit_meals > INT_MAX)
		return (error_exit(INVALID_NUMBERS, d), 1);
	return (0);
}
