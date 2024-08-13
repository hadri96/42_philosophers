/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:42:20 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/13 16:42:20 by hmorand          ###   ########.ch       */
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
		parse_input(ac, av, data);
		fill_data(data);
		dinner_start(data);
		if (all_full(data))
			printf(BGGR"All philos are full!\n"RST);
		destroy_data(data);
		return (0);
	}
	else
	{
		data = NULL;
		error_exit(NOT_ENOUGH_ARGS);
	}
}
