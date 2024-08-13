/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:14:24 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/13 12:14:24 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dead(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLI) - get_long(&philo->mutex, &philo->last_meal_time);
	if (elapsed > philo->data->time_to_die / 1e3)
		return (true);
	return (false);
}

void	ft_sleep(t_philo *philo)
{
	write_status(SLEEPING, philo, DEBUG);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	*monitor_dinner(void *d)
{
	t_data	*data;
	int		i;

	data = (t_data *) d;
	while (!all_threads_running(&data->data_mutex, &data->running_threads,
			data->n_philos))
		;
	while (!get_end(data))
	{
		i = -1;
		while (++ i < data->n_philos)
		{
			if (is_dead(data->philos + i))
			{
				set_bool(&data->data_mutex, &data->end_sim, true);
				write_status(DEAD, data->philos + i, DEBUG);
			}
		}
	}
	return (NULL);
}
