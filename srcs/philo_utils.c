/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:58:55 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/12 14:53:26 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_data(t_data *data)
{
	free(data);
}

void	error_exit(t_error error, t_data *data)
{
	if (error == NOT_ENOUGH_ARGS)
		printf(BOLD_RED"Error: Incorrect number of arguments\n"RESET);
	else if (error == NON_NUMERIC)
		printf(BOLD_RED"Error: Arguments must be numeric and limit for \
meals in brackets\n"RESET);
	else if (error == INVALID_NUMBERS)
		printf(BOLD_RED"Error: Invalid numeric values\n"RESET);
	else if (error == ERROR_INIT)
		printf(BOLD_RED"Error: Initialization of data\n"RESET);
	else if (error == FULL_ERROR)
		printf(BOLD_RED"Error: Philos are full or dead\n"RESET);
	if (data)
		destroy_data(data);
	exit(EXIT_FAILURE);
}

void	display_data(t_data *data)
{
	printf(BOLD_WHITE"number of philos: %ld\n"RESET, data->n_philos);
	printf(BOLD_WHITE"time to die: %ld\n"RESET, data->time_to_die);
	printf(BOLD_WHITE"time to eat: %ld\n"RESET, data->time_to_eat);
	printf(BOLD_WHITE"time to sleep: %ld\n"RESET, data->time_to_sleep);
	printf(BOLD_WHITE"limit of meals: %ld\n"RESET, data->limit_meals);
}
