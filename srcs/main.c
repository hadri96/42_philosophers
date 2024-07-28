/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:18:38 by hmorand           #+#    #+#             */
/*   Updated: 2024/07/28 17:18:38 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	//t_data	data;

	(void)	av;
	if (ac == 5 || ac == 6)
	{
		return (0);
	}
	else
		error_exit("Wrong input!");
}
