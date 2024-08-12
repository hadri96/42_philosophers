/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:40:03 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/12 17:40:03 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	wait_all_threads(philo->data);

	while (!get_end(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		thinking(philo);

	}
}


void	dinner_start(t_data *data)
{
	int	i;

	if (data->limit_meals == 0)
		return ;
	else if (data->n_philos)
		;
	else
	{
		i = -1;
		while (++i < data->n_philos)
			safe_thread_handle(&data->philos[i].thread_id, dinner_simulation,
				&data->philos[i], CREATE);
	}
	data->start_sim = get_time(MILLI);
	set_bool(&data->data_mutex, &data->all_ready, true);
	i = -1;
	while (++i < data->n_philos)
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);

}


