/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:41:33 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/12 13:41:33 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		data = init_data();
		parse_input(ac, av, data);
		display_data(data);

		// if (init_data(&data))
		// 	return (1);
		// if (init_philos(&data))
		// 	return (1);
		// if (start_simulation(&data))
		// 	return (1);
		// if (destroy_data(&data)) (philos full or dead)
		// 	return (1);
		// return (0);
		destroy_data(data);
		return (0);
	}
	else
	{
		data = NULL;
		error_exit(NOT_ENOUGH_ARGS, data);
		return (1);
	}
}
