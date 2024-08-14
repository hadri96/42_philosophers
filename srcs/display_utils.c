/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:02:33 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 13:02:33 by hmorand          ###   ########.ch       */
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

void	write_status_debug(t_state state, t_philo *philo, long elapsed)
{
	if (state == TAKE_FIRST && !get_end(philo->data))
		printf("%6ld"Y" %d has taken the 1° fork 🍴\n"
			"\t\t\t"BL"[%ld ]\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (state == TAKE_SECOND && !get_end(philo->data))
		printf("%6ld"Y" %d has taken the 2° fork 🍴\n"
			"\t\t\t"BL"[%ld ]\n"RST, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (state == EATING && !get_end(philo->data))
		printf("%6ld"GR" %d is eating 🍝\n"
			"\t\t\t"BL"[%6ld ]\n"RST, elapsed, philo->id, philo->meals_counter);
	else if (state == SLEEPING && !get_end(philo->data))
		printf("%6ld"CY" %d is sleeping 💤\n", elapsed, philo->id);
	else if (state == THINKING && !get_end(philo->data))
		printf("%6ld"PU" %d is thinking 💭\n", elapsed, philo->id);
	else if (state == DEAD)
		printf(RED"\t\t💀💀💀%6ld %d died 💀💀💀\n"RST, elapsed, philo->id);
}

int	write_status(t_state state, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLI) - philo->data->start_sim;
	if (get_bool(&philo->mutex, &philo->full) == 1)
		return (EXIT_SUCCESS);
	if (get_bool(&philo->mutex, &philo->full) == -1
		|| safe_mutex_handle(&philo->data->display, LOCK))
		return (EXIT_FAILURE);
	else
	{
		if ((state == TAKE_FIRST || state == TAKE_SECOND)
			&& !get_end(philo->data))
			printf("%ld"Y" %d has taken a fork\n" RST, elapsed, philo->id);
		else if (state == EATING && !get_end(philo->data))
			printf("%ld"GR" %d is sleeping\n" RST, elapsed, philo->id);
		else if (state == EATING && !get_end(philo->data))
			printf("%ld"CY" %d is eating\n" RST, elapsed, philo->id);
		else if (state == EATING && !get_end(philo->data))
			printf("%ld"MG" %d is thinking\n" RST, elapsed, philo->id);
		else if (state == DEAD)
			printf("%ld"RED" %d died\n" RST, elapsed, philo->id);
	}
	if (safe_mutex_handle(&philo->data->display, UNLOCK))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
