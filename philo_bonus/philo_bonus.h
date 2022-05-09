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
# include <signal.h>

# include <semaphore.h>
# include <fcntl.h>

# define FORK			1
# define EATING			2
# define SLEEPING		3
# define THINKING		4

typedef struct timeval	t_timeval;

typedef struct s_args
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				eat_counter;
	t_timeval		program_start_time;
	long			start_time;
	long			start_eat;
	int				counter;
	int				pids[200];
	sem_t			*fork;
	sem_t			*entry_point;
}				t_args;

void	*philo(t_args *data);
void	*ft_memset(void *b, int c, size_t len);
int		ft_atoi(const char *str);
void	ft_usleep(long int time);
long	ft_current_time(void);
void	make_philo(t_args *data);
void	exit_philo(t_args *data);
int		ft_philo_eating(t_args *data);
int		ft_philo_sleeping(t_args *data);
int		ft_philo_thinking(t_args *data);
int		ft_printf(t_args *data, int flag);
t_args	*data_init(int argc, char **argv);
void	ft_sem_init(t_args *data);
void	delete_sem(t_args *data);
void	*monitor(void *data);

#endif