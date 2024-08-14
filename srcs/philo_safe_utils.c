/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_safe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:26:03 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/14 14:26:30 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (EXIT_SUCCESS);
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		return (error_exit(MUTEX_INVALID), 1);
	else if (status == EINVAL && opcode == INIT)
		return (error_exit(ATTR_INVALID), 1);
	else if (status == EDEADLK)
		return (error_exit(DEAD_MUTEX), 1);
	else if (status == EPERM)
		return (error_exit(NO_LOCK), 1);
	else if (status == ENOMEM)
		return (error_exit(NO_MEMORY), 1);
	else if (status == EBUSY)
		return (error_exit(LOCKED), 1);
	return (EXIT_FAILURE);
}

int	safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		return (handle_mutex_error(pthread_mutex_lock(mutex), opcode));
	else if (opcode == UNLOCK)
		return (handle_mutex_error(pthread_mutex_unlock(mutex), opcode));
	else if (opcode == INIT)
		return (handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode));
	else if (opcode == DESTROY)
		return (handle_mutex_error(pthread_mutex_destroy(mutex), opcode));
	else
		return (error_exit(MUTEX_INIT), 1);
}

static int	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (EXIT_SUCCESS);
	else if (status == EAGAIN && (opcode == LOCK || opcode == UNLOCK))
		return (error_exit(NO_RESOURCE), 1);
	else if (status == EINVAL && opcode == CREATE)
		return (error_exit(ATTR_INVALID), 1);
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		return (error_exit(NOT_JOINABLE), 1);
	else if (status == ESRCH)
		return (error_exit(THREAD_NOT_FOUND), 1);
	else if (status == EDEADLK)
		return (error_exit(DEADLOCK), 1);
	else if (status == EPERM)
		return (error_exit(NOT_OWNER), 1);
	return (EXIT_FAILURE);
}

int	safe_thread_handle(pthread_t *thread, void *(*func) (void *),
	void *data, t_opcode op)
{
	if (op == CREATE)
		return (handle_thread_error(pthread_create(
					thread, NULL, func, data), op));
	else if (op == JOIN)
		return (handle_thread_error(pthread_join(*thread, NULL), op));
	else if (op == DETACH)
		return (handle_thread_error(pthread_detach(*thread), op));
	else
		return (error_exit(THREAD_INIT), 1);
}
