/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:34:14 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/03 18:34:54 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# include <semaphore.h>
# include <fcntl.h>

# define SUCCESS		0
# define EATING			1
# define SLEEPING		2
# define THINKING		3
# define FORK			4

typedef struct timeval	t_timeval;

typedef struct s_args
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				eat_counter;
	t_timeval		program_start_time;
	long			start_time;
}				t_args;

typedef struct s_philo
{
	t_args			*in_data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	int				id;
	int				number_of_eat;
	t_timeval		program_start_time;
	t_timeval		last_eating_time;
	int				finish_act;
	long			start_eat;
	pthread_mutex_t	*entry_point;
	pthread_mutex_t	*finish_mut;
	int 			pid;

}				t_philo;

#endif