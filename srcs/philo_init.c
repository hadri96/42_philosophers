/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:31:17 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/13 12:31:17 by hmorand          ###   ########.ch       */
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

static void	init_philos(t_data *data)
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
		safe_mutex_handle(&philo->mutex, INIT);
		assign_forks(philo, data->forks, i);
	}
}

void	fill_data(t_data *data)
{
	int	i;

	data->end_sim = false;
	data->all_ready = false;
	data->running_threads = 0;
	safe_mutex_handle(&data->data_mutex, INIT);
	safe_mutex_handle(&data->display, INIT);
	data->philos = safe_malloc(sizeof(t_philo) * data->n_philos);
	data->forks = safe_malloc(sizeof(t_fork) * data->n_philos);
	i = -1;
	while (++i < data->n_philos)
	{
		safe_mutex_handle(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	init_philos(data);
}
