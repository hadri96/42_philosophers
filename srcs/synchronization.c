/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:10:59 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/13 12:11:14 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_data	*data)
{
	while (!get_bool(&data->data_mutex, &data->all_ready))
		;
}

bool	all_threads_running(t_mutex *mutex, long *threads, long n_philos)
{
	bool	running;

	running = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == n_philos)
		running = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (running);
}

void	increase_long(t_mutex *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}
