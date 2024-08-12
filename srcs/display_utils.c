/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:06:23 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/12 18:08:03 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_data(t_data *data)
{
	printf(BGWH"number of philos: %ld\n"RST, data->n_philos);
	printf(BGWH"time to die: %ld\n"RST, data->time_to_die);
	printf(BGWH"time to eat: %ld\n"RST, data->time_to_eat);
	printf(BGWH"time to sleep: %ld\n"RST, data->time_to_sleep);
	printf(BGWH"limit of meals: %ld\n"RST, data->limit_meals);
}

void	write_status(t_state state, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLI);
	if (philo->full) // thread_safe
		return ;
	safe_mutex_handle(&philo->data->display, LOCK);
	if (debug)
		write_status_debug(state, philo, elapsed);
	else
	{
		if ((state == TAKE_FIRST || state == TAKE_SECOND)
			&& !get_end(philo->data))
			printf("%-6ld"Y" %d has taken a fork\n" RST,
				elapsed, philo->id);
		else if (state == EATING && !get_end(philo->data))
			printf("%-6ld"GR" %d is spleeping\n" RST, elapsed, philo->id);
		else if (state == EATING && !get_end(philo->data))
			printf("%-6ld"GR" %d is eating\n" RST, elapsed, philo->id);
		else if (state == EATING && !get_end(philo->data))
			printf("%-6ld"GR" %d is thinking\n" RST, elapsed, philo->id);
		else if (state == DEAD && !get_end(philo->data))
			printf("%-6ld"GR" %d is dead\n" RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->data->display, UNLOCK);
}
