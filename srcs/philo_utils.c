/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:21:12 by hmorand           #+#    #+#             */
/*   Updated: 2024/07/28 16:21:46 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *message)
{
	printf(BOLD_RED"%s\n"RESET, message);
	exit(EXIT_FAILURE);
}
