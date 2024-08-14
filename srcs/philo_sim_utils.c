/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:51:56 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 15:52:44 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_is_dead(t_philo *philo)
{
	long	elapsed;
	long	last_meal;
	int		is_full;

	is_full = get_bool(&philo->mutex, &philo->full);
	if (is_full == -1)
		return (-1);
	else if (is_full)
		return (EXIT_SUCCESS);
	last_meal = get_long(&philo->mutex, &philo->last_meal_time);
	if (last_meal == -1)
		return (-1);
	elapsed = get_time(MILLI) - last_meal;
	if (elapsed > philo->data->time_to_die / 1e3)
	{
		if (set_bool(&philo->data->data_mutex, &philo->data->end_sim, true)
			|| write_status(DEAD, philo))
			return (-1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_sleep(t_philo *philo)
{
	if (write_status(SLEEPING, philo))
		return (EXIT_FAILURE);
	ft_usleep(philo->data->time_to_sleep, philo->data);
	return (EXIT_SUCCESS);
}

void	*one_philo(void *p)
{
	t_philo	*philo;
	int		end;

	philo = (t_philo *) p;
	end = 1;
	if (wait_all_threads(philo->data)
		|| set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLI))
		|| increase_long(&philo->data->data_mutex,
			&philo->data->running_threads))
		return ((void *) 1);
	if (write_status(TAKE_FIRST, philo))
		return ((void *)1);
	end = get_end(philo->data);
	if (end == -1)
		return ((void *)1);
	while (!end)
	{
		ft_usleep(200, philo->data);
		end = get_end(philo->data);
		if (end == -1)
			return ((void *)1);
	}
	if (end)
		return ((void *)1);
	return (NULL);
}

void	*monitor_dinner(void *d)
{
	t_data	*data;
	int		i;
	int		is_dead;

	data = (t_data *) d;
	i = 1;
	while (!all_threads_running(&data->data_mutex,
			&data->running_threads, data->n_philos))
		;
	if (all_threads_running(&data->data_mutex, &data->running_threads,
			data->n_philos) == -1)
		return ((void *)1);
	while (!get_end(data))
	{
		i = -1;
		while (++ i < data->n_philos)
		{
			is_dead = check_is_dead(data->philos + i);
			if (is_dead)
				break ;
		}
	}
	if (get_end(data) == -1 || is_dead == -1)
		return ((void *)1);
	return ((void *)0);
}
