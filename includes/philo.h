/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:40:35 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/16 17:41:22 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>
# include <limits.h>
//# include "../libft/libft.h"

# define BGWH	"\033[1;37m"
# define BGR	"\033[1;31m"
# define RED	"\033[0;31m"
# define BGGR	"\033[1;32m"
# define GR		"\033[0;32m"
# define BGY	"\033[1;33m"
# define Y		"\033[0;33m"
# define BGB	"\033[1;34m"
# define BL		"\033[0;34m"
# define BGMG	"\033[1;35m"
# define MG		"\033[0;35m"
# define BGCY	"\033[1;36m"
# define CY		"\033[0;36m"
# define BGPU	"\033[1;35m"
# define PU		"\033[0;35m"
# define BGBLA	"\033[1;30m"
# define RST	"\033[0m"
# define DEBUG 0

typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mutex	fork;
	long	fork_id;
}	t_fork;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST,
	TAKE_SECOND,
	DEAD,
}	t_state;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef enum e_error
{
	ERROR_INIT,
	NOT_ENOUGH_ARGS,
	NON_NUMERIC,
	INVALID_NUMBERS,
	MUTEX_INVALID,
	BUSY,
	NO_MEMORY,
	NO_LOCK,
	LOCKED,
	DEAD_MUTEX,
	ATTR_INVALID,
	NO_RESOURCE,
	NOT_JOINABLE,
	THREAD_NOT_FOUND,
	DEADLOCK,
	NOT_OWNER,
	THREAD_INIT,
	MUTEX_INIT,
	CHRONO,
	WRONG_UNIT
}	t_error;

typedef enum e_unit
{
	MICRO,
	MILLI,
	SEC
}	t_unit;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	int			full;
	long		last_meal_time;
	t_fork		*second_fork;
	t_fork		*first_fork;
	t_mutex		mutex;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	long		n_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		limit_meals;
	long		start_sim;
	long		running_threads;
	int			all_ready;
	int			end_sim;
	int			error;
	pthread_t	monitor;
	t_mutex		data_mutex;
	t_mutex		display;
	t_fork		*forks;
	t_philo		*philos;
}	t_data;

/*****************************************************************************/
/*                                                                           */
/*                                  PARSING                                  */
/*                                                                           */
/*****************************************************************************/

t_data	*init_data(void);
int		parse_input(int ac, char **av, t_data *data);

/*****************************************************************************/
/*                                                                           */
/*                                   UTILS                                   */
/*                                                                           */
/*****************************************************************************/

void	error_exit(t_error error);
int		destroy_data(t_data *data);

/* DISPLAY UTILS */

void	display_data(t_data *data);
void	write_status_debug(t_state state, t_philo *philo, long elapsed);
int		write_status(t_state state, t_philo *philog);

/* STRING UTILS */

bool	ft_strisdigit(char *str);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
long	ft_atol(const char *str);

/*****************************************************************************/
/*                                                                           */
/*                                 SAFE UTILS                                */
/*                                                                           */
/*****************************************************************************/

int		safe_mutex_handle(t_mutex *mutex, t_opcode opcode);
int		safe_thread_handle(pthread_t *thread, void *(*func) (void *),
			void *data, t_opcode op);
void	*safe_malloc(size_t size);

/*****************************************************************************/
/*                                                                           */
/*                               INITIALIZATION                              */
/*                                                                           */
/*****************************************************************************/

int		fill_data(t_data *data);

/*****************************************************************************/
/*                                                                           */
/*                                GETTERS/SETTERS                            */
/*                                                                           */
/*****************************************************************************/

int		set_bool(t_mutex *mutex, int *dest, int value);
int		get_bool(t_mutex *mutex, int *value);
int		get_end(t_data *data);
int		set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *value);
int		increase_long(t_mutex *mutex, long *value);

/*****************************************************************************/
/*                                                                           */
/*                                SYNCHRONIZATION                            */
/*                                                                           */
/*****************************************************************************/

int		wait_all_threads(t_data	*data);
int		all_threads_running(t_mutex *mutex, long *threads, long n_philos);

/*****************************************************************************/
/*                                                                           */
/*                                  TIME UTILS                               */
/*                                                                           */
/*****************************************************************************/

long	get_time(t_unit unit);
int		ft_usleep(long usec, t_data *data);

/*****************************************************************************/
/*                                                                           */
/*                                  SIMULATION                               */
/*                                                                           */
/*****************************************************************************/

/* SIMULATION UTILS */

void	*monitor_dinner(void *d);
void	*one_philo(void *p);
int		ft_sleep(t_philo *philo);

/* SIMULATION MAIN */

int		dinner_start(t_data *data);

#endif
