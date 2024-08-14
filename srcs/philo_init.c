/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:54:58 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 11:58:42 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	philo->first_fork = forks + ((i + 1) % philo->data->n_philos);
	philo->second_fork = forks + i;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = forks + i;
		philo->second_fork = forks + ((i + 1) % philo->data->n_philos);
	}
}

static int	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->n_philos)
	{
		philo = data->philos + i;
		philo->id = i;
		philo->full = false;
		philo->meals_counter = 0;
		philo->data = data;
		if (safe_mutex_handle(&philo->mutex, INIT))
			return (EXIT_FAILURE);
		assign_forks(philo, data->forks, i);
	}
	return (EXIT_SUCCESS);
}

int	fill_data(t_data *data)
{
	int	i;

	data->end_sim = false;
	data->all_ready = false;
	data->running_threads = 0;
	if (safe_mutex_handle(&data->data_mutex, INIT)
		|| safe_mutex_handle(&data->display, INIT))
		return (EXIT_FAILURE);
	data->philos = safe_malloc(sizeof(t_philo) * data->n_philos);
	data->forks = safe_malloc(sizeof(t_fork) * data->n_philos);
	if (!data->philos || !data->forks)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < data->n_philos)
	{
		if (safe_mutex_handle(&data->forks[i].fork, INIT))
			return (EXIT_FAILURE);
		data->forks[i].fork_id = i;
	}
	init_philos(data);
	return (EXIT_SUCCESS);
}
