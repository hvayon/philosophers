/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:13 by natalia           #+#    #+#             */
/*   Updated: 2022/05/02 14:54:45 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //delite

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS        0

long ft_current_time(void)
{
	long value;
	t_timeval time;
	gettimeofday(&time, NULL);
	value = time.tv_sec * 1000 + time.tv_usec / 1000;
	return(value);
}

void	ft_usleep(long int time)
{
	long i;
	i = ft_current_time();
	while((ft_current_time() - i) < time)
		usleep(100);
}


t_args *data_init(int argc, char **argv)
{
		t_args *data;
		int i;

		i = 0;
		data = malloc(sizeof(t_args));
		while (++i < argc)
		{
		if (ft_atoi(argv[i]) <= 0)
			return (NULL);
		}
		data->number_of_philosophers = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		data->eat_counter = 0;
		gettimeofday(&data->program_start_time, 0);
		data->number_of_eat = -1;
		if (argc == 6)
			data->number_of_eat = ft_atoi(argv[5]);
		return(data);
}

t_philo *ph_init(t_args *data, pthread_mutex_t entry_point)
{
			t_philo *ph;
			int       i;

			i = 0;
			ph = malloc(sizeof(t_philo) * data->number_of_philosophers);
			if (!ph)
					return(NULL);
			while(i < data->number_of_philosophers)
			{
				ph[i].id = i + 1;
				ph[i].number_of_eat = data->number_of_eat;
				ph[i].in_data = data;
				ph[i].program_start_time = data->program_start_time;
				ph[i].entry_point = &entry_point;
				ph[i].start_eat = ft_current_time();
				gettimeofday(&ph[i].last_eating_time, 0);
				pthread_mutex_init(&ph[i].right_fork, NULL);
				i++;
			}
			i = 1;
			while(i < data->number_of_philosophers)
			{
				ph[i].left_fork = &ph[i - 1].right_fork;
				i++;
			}
			ph[0].left_fork = &ph[i - 1].right_fork;
			return(ph);
}

long  ft_current_pr_time(t_philo *ph)
{
		t_timeval current_time;
		long    value;
		gettimeofday(&current_time, NULL);
		value = (current_time.tv_sec - ph->program_start_time.tv_sec) * 1000 + (current_time.tv_usec - ph->program_start_time.tv_usec)  / 1000;
		return(value);
}

//----разбить эту функцию по функциям eat, sleep, think
void *philo(void *philo)
{
	t_philo	*ph;
	
	ph = (t_philo *)philo;
	if (ph->id % 2)
		usleep(2500);
	while(ph->number_of_eat)
	{
		pthread_mutex_lock(ph->left_fork); 
		pthread_mutex_lock(ph->entry_point);
		printf("%ld %d has taken a fork\n", ft_current_pr_time(ph), ph->id);
		pthread_mutex_unlock(ph->entry_point);
		pthread_mutex_lock(&ph->right_fork);
		pthread_mutex_lock(ph->entry_point);
		printf("%ld %d has taken a fork\n",  ft_current_pr_time(ph), ph->id);
		pthread_mutex_unlock(ph->entry_point);
		ph->start_eat = ft_current_time();
		pthread_mutex_lock(ph->entry_point);
		printf("%ld %d is eating\n", ft_current_pr_time(ph), ph->id);
		pthread_mutex_unlock(ph->entry_point);
		ft_usleep(ph->in_data->time_to_eat);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(&ph->right_fork);
		pthread_mutex_lock(ph->entry_point);
		printf("%ld %d is sleeping\n", ft_current_pr_time(ph), ph->id);
		pthread_mutex_unlock(ph->entry_point);
		ft_usleep(ph->in_data->time_to_sleep);
		pthread_mutex_lock(ph->entry_point);
		printf("%ld %d is thinking\n", ft_current_pr_time(ph), ph->id);
		pthread_mutex_unlock(ph->entry_point);
		if (ph->number_of_eat != -1)
			ph->number_of_eat -= 1;
	}
	ph->in_data->eat_counter++;
	ph->finish_act = 1;
	return (NULL);
}

int	is_dead(t_philo *ph, int i)
{
	t_timeval current_time;
	while (i < ph->in_data->number_of_philosophers)
	{
		if (ph->in_data->number_of_philosophers == ph->in_data->eat_counter)
		{
			pthread_mutex_lock(ph->entry_point);
			printf("All the philosopher has eaten at least %d times each\n", ph->in_data->number_of_eat);
			return (1);
		}
		if (!ph[i].finish_act)
		{	
			if ((ft_current_time() - ph[i].start_eat) >= (ph->in_data->time_to_die))
			{
				pthread_mutex_lock(ph->entry_point);
				printf("%ld %d died\n", ft_current_time() - ph->in_data->start_time, ph->id);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	*monitor(void *philo)
{
	int		i;
	t_philo	*ph;

	ph = (t_philo *)philo;
	usleep(100);
	while (1)
	{
		i = 0;
		if (is_dead(ph, i))
			break ;
	}
	return (NULL);
}

pthread_t  *make_threads(t_args *data, t_philo *ph)
{
		int num;
		int status;
		int i;
		pthread_t	*th;
		int			th_ok;
		
		th = (pthread_t *)malloc(sizeof(pthread_t) * data->number_of_philosophers); // зачем записывать в malloc
		if (!th)
			free(th);
		i = 0;
		while (i < data->number_of_philosophers)
		{
			num = pthread_create(&th[i], 0, philo, &(ph[i])); 
			if (num)
				return (NULL);
			i++;
		}
		monitor(ph);
		i = 0;
		while(i < data->number_of_philosophers)
		{
			status = pthread_join(th[i], 0);
			if (status != SUCCESS)
					printf("main error: can't join thread, status = %d\n", status);
			i++;
		}
		return(th);
}

void	kill_philo(t_philo *ph, pthread_t	*th)
{
	int i;
	
	i = 0;
	while(ph->in_data->number_of_philosophers > i)
	{
		
		pthread_mutex_destroy(&ph[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(ph->entry_point);
	free(th);
	free(ph->in_data);
	free(ph);
}

int main(int argc, char **argv)
{
		t_args  *data;
		t_philo *ph;
		pthread_t *th;
		pthread_mutex_t	entry_point;

		pthread_mutex_init(&entry_point, NULL);
		if (argc > 6 || argc < 5)
			return (1);
		data = data_init(argc, argv);
		if (!data)
			return(1);
		ph = ph_init(data, entry_point);
		if (!ph)
			return(1);
		th = make_threads(data, ph);
		if (!th)
			return(1);
		kill_philo(ph, th);
		return(0);
}