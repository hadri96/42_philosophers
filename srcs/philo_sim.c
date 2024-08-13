/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:16:38 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/13 15:47:25 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST, philo, DEBUG);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND, philo, DEBUG);
	set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLI));
	increase_long(&philo->mutex, &philo->meals_counter);
	write_status(EATING, philo, DEBUG);
	ft_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->limit_meals > 0
		&& philo->meals_counter == philo->data->limit_meals)
		set_bool(&philo->mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	think(t_philo *philo)
{
	long	t_think;

	write_status(THINKING, philo, DEBUG);
	ft_usleep(philo->data->n_philos / 2 * 1e3, philo->data);
	if (philo->data->n_philos % 2 == 0)
		return ;
	t_think = philo->data->time_to_eat * 2 - philo->data->time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42, philo->data);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	wait_all_threads(philo->data);
	set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLI));
	increase_long(&philo->data->data_mutex,
		&philo->data->running_threads);
	while (!get_end(philo->data))
	{
		if (get_bool(&philo->mutex, &philo->full))
			break ;
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	*one_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	wait_all_threads(philo->data);
	set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLI));
	increase_long(&philo->data->data_mutex, &philo->data->running_threads);
	write_status(TAKE_FIRST, philo, DEBUG);
	while (!get_end(philo->data))
		ft_usleep(200, philo->data);
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	if (data->limit_meals == 0)
		return ;
	else if (data->n_philos == 1)
		safe_thread_handle(&data->philos[0].thread_id,
			one_philo, &data->philos[0], CREATE);
	else
	{
		i = -1;
		while (++i < data->n_philos)
			safe_thread_handle(&data->philos[i].thread_id, dinner_simulation,
				&data->philos[i], CREATE);
	}
	safe_thread_handle(&data->monitor, monitor_dinner, data, CREATE);
	data->start_sim = get_time(MILLI);
	set_bool(&data->data_mutex, &data->all_ready, true);
	i = -1;
	while (++i < data->n_philos)
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&data->data_mutex, &data->end_sim, true);
	safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
}
