/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:44:37 by natalia           #+#    #+#             */
/*   Updated: 2022/05/03 14:08:53 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define SUCCESS			0
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

}				t_philo;

int			ft_atoi(const char *str);
int			ft_printf(t_philo *ph, int flag);
void		*philo(void *philo);
long		ft_current_time(void);
long		ft_current_pr_time(t_philo *ph);
void		ft_usleep(long int time);
t_philo		*ph_init(t_args *data, pthread_mutex_t entry_point, \
										pthread_mutex_t finish);
pthread_t	*make_threads(t_args *data, t_philo *ph);

#endif
