/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:07:51 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 12:07:51 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = safe_malloc(sizeof(t_data));
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
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (!ft_strisdigit(av[1]) || !ft_strisdigit(av[2])
			|| !ft_strisdigit(av[3]) || !ft_strisdigit(av[4]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parse_input(int ac, char **av, t_data *d)
{
	char	*times;

	if (check_numeric(ac, av, &times))
		return (error_exit(NON_NUMERIC), 1);
	d->n_philos = ft_atol(av[1]);
	d->time_to_die = ft_atol(av[2]) * 1e3;
	d->time_to_eat = ft_atol(av[3]) * 1e3;
	d->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (ac == 6)
	{
		d->limit_meals = ft_atol(times);
		free(times);
	}
	else
		d->limit_meals = -1;
	if (d->time_to_die < 6e4 || d->time_to_eat < 6e4 || d->time_to_sleep < 6e4
		|| (ac == 6 && d->limit_meals < 1) || d->n_philos > INT_MAX
		|| d->time_to_die > INT_MAX || d->time_to_eat > INT_MAX
		|| d->time_to_sleep > INT_MAX || d->limit_meals > INT_MAX)
		return (error_exit(INVALID_NUMBERS), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
