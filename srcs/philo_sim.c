/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:22:35 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 15:22:35 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo)
{
	if (safe_mutex_handle(&philo->first_fork->fork, LOCK)
		|| write_status(TAKE_FIRST, philo)
		|| safe_mutex_handle(&philo->second_fork->fork, LOCK)
		|| write_status(TAKE_SECOND, philo)
		|| set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLI))
		|| increase_long(&philo->mutex, &philo->meals_counter)
		|| write_status(EATING, philo))
		return (EXIT_FAILURE);
	ft_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->limit_meals > 0
		&& philo->meals_counter == philo->data->limit_meals)
	{
		if (set_bool(&philo->mutex, &philo->full, true))
			return (EXIT_FAILURE);
	}
	if (safe_mutex_handle(&philo->first_fork->fork, UNLOCK)
		|| safe_mutex_handle(&philo->second_fork->fork, UNLOCK))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	think(t_philo *philo)
{
	long	t_think;

	if (write_status(THINKING, philo))
		return (EXIT_FAILURE);
	ft_usleep(philo->data->n_philos / 2 * 1e3, philo->data);
	if (philo->data->n_philos % 2 == 0)
		return (EXIT_SUCCESS);
	t_think = philo->data->time_to_eat * 2 - philo->data->time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42, philo->data);
	return (EXIT_SUCCESS);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	if (wait_all_threads(philo->data) == -1
		|| set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLI))
		|| increase_long(&philo->data->data_mutex,
			&philo->data->running_threads))
		return ((void *)1);
	while (!get_end(philo->data) && get_end(philo->data) != 1)
	{
		if (get_bool(&philo->mutex, &philo->full)
			|| get_bool(&philo->mutex, &philo->full) == -1)
			break ;
		if (eat(philo) || ft_sleep(philo) || think(philo))
			return ((void *)1);
	}
	if (get_bool(&philo->mutex, &philo->full) == -1)
		return ((void *)1);
	return ((void *)0);
}

int	dinner_part_2(t_data *data)
{
	int	i;

	if (safe_thread_handle(&data->monitor, monitor_dinner, data, CREATE))
		return (EXIT_FAILURE);
	data->start_sim = get_time(MILLI);
	if (set_bool(&data->data_mutex, &data->all_ready, true))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < data->n_philos)
	{
		if (safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN))
			return (EXIT_FAILURE);
	}
	if (set_bool(&data->data_mutex, &data->end_sim, true)
		|| safe_thread_handle(&data->monitor, NULL, NULL, JOIN))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	dinner_start(t_data *data)
{
	int	i;

	if (data->limit_meals == 0)
		return (EXIT_SUCCESS);
	else if (data->n_philos == 1)
	{
		if (safe_thread_handle(&data->philos[0].thread_id,
				one_philo, &data->philos[0], CREATE))
			return (EXIT_FAILURE);
	}
	else
	{
		i = -1;
		while (++i < data->n_philos)
		{
			if (safe_thread_handle(&data->philos[i].thread_id,
					dinner_simulation, &data->philos[i], CREATE))
				return (EXIT_FAILURE);
		}
	}
	if (dinner_part_2(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
