/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:48:03 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 12:49:05 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_bool(t_mutex *mutex, int *dest, int value)
{
	if (safe_mutex_handle(mutex, LOCK))
		return (EXIT_FAILURE);
	*dest = value;
	if (safe_mutex_handle(mutex, UNLOCK))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_bool(t_mutex *mutex, int *value)
{
	int	ret;

	if (safe_mutex_handle(mutex, LOCK))
		return (-1);
	ret = *value;
	if (safe_mutex_handle(mutex, UNLOCK))
		return (-1);
	return (ret);
}

int	get_end(t_data *data)
{
	return (get_bool(&data->data_mutex, &data->end_sim));
}

int	set_long(t_mutex *mutex, long *dest, long value)
{
	if (safe_mutex_handle(mutex, LOCK))
		return (EXIT_FAILURE);
	*dest = value;
	if (safe_mutex_handle(mutex, UNLOCK))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

long	get_long(t_mutex *mutex, long *value)
{
	long	ret;

	if (safe_mutex_handle(mutex, LOCK))
		return (-1);
	ret = *value;
	if (safe_mutex_handle(mutex, UNLOCK))
		return (-1);
	return (ret);
}
