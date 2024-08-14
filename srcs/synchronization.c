/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:51:21 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 15:51:27 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_all_threads(t_data	*data)
{
	int	result;

	result = get_bool(&data->data_mutex, &data->all_ready);
	while (result == 0)
		result = get_bool(&data->data_mutex, &data->all_ready);
	if (result == 1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	all_threads_running(t_mutex *mutex, long *threads, long n_philos)
{
	int	running;

	running = 0;
	if (safe_mutex_handle(mutex, LOCK))
		return (-1);
	if (*threads == n_philos || n_philos == 1)
		running = 1;
	if (safe_mutex_handle(mutex, UNLOCK))
		return (-1);
	return (running);
}

int	increase_long(t_mutex *mutex, long *value)
{
	if (safe_mutex_handle(mutex, LOCK))
		return (EXIT_FAILURE);
	(*value)++;
	if (safe_mutex_handle(mutex, UNLOCK))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
