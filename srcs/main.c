/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:40:19 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/12 16:40:19 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	pthread_t	t1, t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	pthread_mutex_destroy(&mutex);
	if (ac == 5 || ac == 6)
	{
		data = init_data();
		parse_input(ac, av, data);
		fill_data(data);

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
		error_exit(NOT_ENOUGH_ARGS);
	}
}
