/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:34:00 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/03 18:47:44 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *data)
{
	t_args	*d;

	d = (t_args *)data;
	while (1)
	{
		if ((ft_current_time() - d->start_eat) >= (d->time_to_die))
		{
			sem_wait(d->entry_point);
			printf("%ld %d died\n", ft_current_time() - d->start_time, \
															d->counter);
			exit (0);
		}
		usleep(900);
	}
}

int	ft_printf(t_args *data, int flag)
{
	long	value;

	value = ft_current_time() - data->start_time;
	sem_wait(data->entry_point);
	if (flag == 1)
		printf("%ld %d is eating\n", value, data->counter);
	if (flag == 2)
		printf("%ld %d is sleeping\n", value, data->counter);
	if (flag == 3)
		printf("%ld %d is thinking\n", value, data->counter);
	if (flag == 4)
		printf("%ld %d has taken a fork\n", value, data->counter);
	sem_post(data->entry_point);
	return (0);
}

void	make_philo(t_args *data)
{
	data->counter = 0;
	while (data->counter < data->number_of_philo)
	{
		data->pids[data->counter] = fork();
		if (data->pids[data->counter] == 0)
			break ;
		if (data->pids[data->counter] == -1)
		{
			printf("Error create fork");
			break ;
		}
		data->counter++;
	}
}

void	*philo(t_args *data)
{
	pthread_t	check_monitor;
	int			data_ok;

	data->counter++;
	data_ok = pthread_create(&check_monitor, NULL, monitor, data);
	if (data_ok)
		return (NULL);
	pthread_detach(check_monitor);
	if (!(data->counter % 2))
		usleep(500);
	data->start_time = ft_current_time();
	while (data->number_of_eat)
	{
		ft_philo_eating(data);
		ft_philo_sleeping(data);
		ft_philo_thinking(data);
		if (data->number_of_eat != -1)
			data->number_of_eat -= 1;
	}
	exit(1);
}

void	exit_philo(t_args *data)
{
	int	status;
	int	*arr;
	int	i;

	arr = malloc(sizeof(int) * data->number_of_philo);
	ft_memset(arr, 0, sizeof(int) * data->number_of_philo);
	i = -1;
	while (++i < data->number_of_philo)
	{
		waitpid(-1, &status, 0);
		if (!status)
		{
			i = -1;
			while (++i < data->number_of_philo)
				kill(data->pids[i], SIGTERM);
			break ;
		}
		arr[i] = 1;
	}
	i = -1;
	while (++i < data->number_of_philo)
		if (arr[i] == 0)
			break ;
	if (i == data->number_of_philo)
		printf("All the philosophers has eaten %d times each\n", data->counter);
}
