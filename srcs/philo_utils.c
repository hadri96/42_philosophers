/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:54:43 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/13 11:58:03 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_data(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->n_philos)
	{
		philo = data->philos + i;
		safe_mutex_handle(&philo->mutex, DESTROY);
	}
	safe_mutex_handle(&data->display, DESTROY);
	safe_mutex_handle(&data->data_mutex, DESTROY);
	free(data->forks);
	free(data->philos);
	free(data);
}

void	error_exit_sub(t_error error)
{
	if (error == NOT_OWNER)
		printf(BGR"Error: No appropriate permissions\n"RST);
	else if (error == NO_RESOURCE)
		printf(BGR"Error: Insufficient resources\n"RST);
	else if (error == DEAD_MUTEX)
		printf(BGR"Error: Deadlock was detected\n"RST);
	else if (error == NO_MEMORY)
		printf(BGR"Error: Cannot allocate memory \
for other mutex\n"RST);
	else if (error == NO_LOCK)
		printf(BGR"Error: Current thread does not \
hold a lock on a mutex\n"RST);
	else if (error == LOCKED)
		printf(BGR"Error: Mutex is already locked\n"RST);
	else if (error == THREAD_INIT)
		printf(BGR"Error: Wrong thread code"RST);
	else if (error == MUTEX_INIT)
		printf(BGR"Error: Wrong mutex code"RST);
	else if (error == CHRONO)
		printf(BGR"Error: Issue with time\n"RST);
	else if (error == WRONG_UNIT)
		printf(BGR"Error: Wrong unit of time\n"RST);
	else
		printf(BGR"Error: Unknown error\n"RST);
}

void	error_exit(t_error error)
{
	if (error == NOT_ENOUGH_ARGS)
		printf(BGR"Error: Incorrect number of arguments\n"RST);
	else if (error == NON_NUMERIC)
		printf(BGR"Error: Arguments must be numeric and limit for \
meals in brackets\n"RST);
	else if (error == INVALID_NUMBERS)
		printf(BGR"Error: Invalid numeric values\n"RST);
	else if (error == ERROR_INIT)
		printf(BGR"Error: Initialization of data\n"RST);
	else if (error == MUTEX_INVALID)
		printf(BGR"Error: Value specified by mutex is invalid\n"RST);
	else if (error == ATTR_INVALID)
		printf(BGR"Error: Value specified by attr is invalid\n"RST);
	else if (error == NOT_JOINABLE)
		printf(BGR"Error: Value specified by thread not joinable\n"RST);
	else if (error == THREAD_NOT_FOUND)
		printf(BGR"Error: Thread not found\n"RST);
	else if (error == DEADLOCK)
		printf(BGR"Error: Deadlock was detected\n"RST);
	else
		error_exit_sub(error);
	exit(EXIT_FAILURE);
}
