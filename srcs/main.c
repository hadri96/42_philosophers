/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:20:16 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/10 18:56:50 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (0);
}

int	main(int ac, char **av)
{
	//t_data	data;
	pthread_t	t1, t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	pthread_mutex_destroy(&mutex);
	(void) av;
	(void) ac;
	/* if (ac == 5 || ac == 6)
	{
		return (0);
	}
	else
		error_exit("Wrong input!"); */
	printf("Mails: %d\n", mails);
	return (0);
}
