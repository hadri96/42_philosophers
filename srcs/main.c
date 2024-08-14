/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:11:17 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 14:11:17 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_full(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (!data->philos[i].full)
			return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		data = init_data();
		if (!data)
			return (EXIT_FAILURE);
		if (parse_input(ac, av, data))
			return (EXIT_FAILURE);
		if (fill_data(data) || dinner_start(data))
		{
			destroy_data(data);
			return (EXIT_FAILURE);
		}
		if (all_full(data))
			printf(BGGR"All philos are full!\n"RST);
		return (destroy_data(data));
	}
	else
	{
		data = NULL;
		return (error_exit(NOT_ENOUGH_ARGS), EXIT_FAILURE);
	}
}
