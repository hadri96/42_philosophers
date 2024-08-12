/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_safe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:03:18 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/12 16:03:58 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit(MUTEX_INVALID);
	else if (status == EINVAL && opcode == INIT)
		error_exit(ATTR_INVALID);
	else if (status == EDEADLK)
		error_exit(DEAD_MUTEX);
	else if (status == EPERM)
		error_exit(NO_LOCK);
	else if (status == ENOMEM)
		error_exit(NO_MEMORY);
	else if (status == EBUSY)
		error_exit(LOCKED);
}

void	safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit(MUTEX_INIT);
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EAGAIN && (opcode == LOCK || opcode == UNLOCK))
		error_exit(NO_RESOURCE);
	else if (status == EINVAL && opcode == CREATE)
		error_exit(ATTR_INVALID);
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit(NOT_JOINABLE);
	else if (status == ESRCH)
		error_exit(THREAD_NOT_FOUND);
	else if (status == EDEADLK)
		error_exit(DEADLOCK);
	else if (status == EPERM)
		error_exit(NOT_OWNER);
}

void	safe_thread_handle(pthread_t *thread, void *(*func) (void *),
t_opcode op, void *data)
{
	if (op == CREATE)
		handle_thread_error(pthread_create(thread, NULL, func, data), op);
	else if (op == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), op);
	else if (op == DETACH)
		handle_thread_error(pthread_detach(*thread), op);
	else
		error_exit(THREAD_INIT);
}
