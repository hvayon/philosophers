/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_live_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:38:09 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/08 18:38:19 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_printf(t_args *data, int flag)
{
	long	value;

	value = ft_current_time() - data->start_time;
	sem_wait(data->entry_point);
	if (flag == 1)
		printf("%ld %d has taken a fork\n", value, data->counter);
	if (flag == 2)
		printf("%ld %d is eating\n", value, data->counter);
	if (flag == 3)
		printf("%ld %d is sleeping\n", value, data->counter);
	if (flag == 4)
		printf("%ld %d is thinking\n", value, data->counter);
	sem_post(data->entry_point);
	return (0);
}

int	ft_philo_eating(t_args *data)
{
	sem_wait(data->fork);
	ft_printf(data, FORK);
	sem_wait(data->fork);
	ft_printf(data, FORK);
	data->start_eat = ft_current_time();
	ft_printf(data, EATING);
	ft_usleep(data->time_to_eat);
	sem_post(data->fork);
	sem_post(data->fork);
	return (0);
}

int	ft_philo_sleeping(t_args *data)
{
	ft_printf(data, SLEEPING);
	ft_usleep(data->time_to_sleep);
	return (0);
}

int	ft_philo_thinking(t_args *data)
{
	ft_printf(data, THINKING);
	return (0);
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
	data->start_time = ft_current_time();
	if (!(data->counter % 2))
		usleep(500);
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
