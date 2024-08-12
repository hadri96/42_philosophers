/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:41:11 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/12 13:41:20 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> //usleep, write
# include <stdlib.h> //malloc, free
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h> // mutex: init destroy lock unlock
					  // threads: create join detach
# include <sys/time.h> // gettimeofday
# include <limits.h>
# include "../libft/libft.h"

#define BOLD_WHITE		"\033[1;37m"
#define BOLD_RED		"\033[1;31m"
#define BOLD_GREEN		"\033[1;32m"
#define BOLD_YELLOW		"\033[1;33m"
#define BOLD_BLUE		"\033[1;34m"
#define BOLD_MAGENTA	"\033[1;35m"
#define BOLD_CYAN		"\033[1;36m"
#define BOLD_BLACK		"\033[1;30m"
#define RESET			"\033[0m"

typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FULL
}	t_state;

typedef enum e_error
{
	ERROR_INIT,
	NOT_ENOUGH_ARGS,
	NON_NUMERIC,
	INVALID_NUMBERS,
	FULL_ERROR
}	t_error;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	long	n_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	limit_meals;
	long	start_sim;
	bool	end_sim;
	t_fork	*forks;
	t_philo	*philos;
}	t_data;

/*****************************************************************************/
/*                                                                           */
/*                                PARSING                                    */
/*                                                                           */
/*****************************************************************************/

t_data	*init_data(void);
int		parse_input(int ac, char **av, t_data *data);

/*****************************************************************************/
/*                                                                           */
/*                                 UTILS                                     */
/*                                                                           */
/*****************************************************************************/

void	error_exit(t_error error, t_data *data);
void	display_data(t_data *data);
void	destroy_data(t_data *data);

#endif
