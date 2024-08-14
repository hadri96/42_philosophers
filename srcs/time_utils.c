/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:55:08 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 12:55:08 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_unit unit)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_exit(CHRONO), -1);
	if (unit == SEC)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (unit == MILLI)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (unit == MICRO)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else
		return (error_exit(WRONG_UNIT), -1);
	return (1);
}

int	ft_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remain;

	start = get_time(MICRO);
	while (get_time(MICRO) - start < usec && get_time(MICRO) != -1)
	{
		if (get_end(data))
			break ;
		elapsed = get_time(MICRO) - start;
		remain = usec - elapsed;
		if (remain > 1e3)
			usleep(remain / 2);
		else
		{
			while (get_time(MICRO) - start < usec && get_time(MICRO) != -1)
				;
		}
	}
	return (EXIT_SUCCESS);
}
