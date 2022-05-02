/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:13 by natalia           #+#    #+#             */
/*   Updated: 2022/05/02 19:53:06 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_eating(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	ft_printf(ph, FORK);
	pthread_mutex_lock(&ph->right_fork);
	ft_printf(ph, FORK);
	pthread_mutex_lock(ph->entry_point);
	ph->start_eat = ft_current_time();
	pthread_mutex_unlock(ph->entry_point);
	ft_printf(ph, EATING);
	ft_usleep(ph->in_data->time_to_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(&ph->right_fork);
	return (0);
}

int	ft_philo_sleeping(t_philo *ph)
{
	ft_printf(ph, SLEEPING);
	ft_usleep(ph->in_data->time_to_sleep);
	return (0);
}

int	ft_philo_thinking(t_philo *ph)
{
	ft_printf(ph, THINKING);
	return (0);
}

void	*philo(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->id % 2)
		usleep(2500);
	while (ph->number_of_eat)
	{
		ft_philo_eating(ph);
		ft_philo_sleeping(ph);
		ft_philo_thinking(ph);
		if (ph->number_of_eat != -1)
			ph->number_of_eat -= 1;
	}
	pthread_mutex_lock(ph->finish_mut);
	ph->in_data->eat_counter++;
	pthread_mutex_unlock(ph->finish_mut);
	pthread_mutex_lock(ph->finish_mut);
	ph->finish_act = 1;
	pthread_mutex_unlock(ph->finish_mut);
	return (NULL);
}

int	ft_printf(t_philo *ph, int flag)
{
	pthread_mutex_lock(ph->entry_point);
	if (flag == 1)
		printf("%ld %d is eating\n", ft_current_pr_time(ph), ph->id);
	if (flag == 2)
		printf("%ld %d is sleeping\n", ft_current_pr_time(ph), ph->id);
	if (flag == 3)
		printf("%ld %d is thinking\n", ft_current_pr_time(ph), ph->id);
	if (flag == 4)
		printf("%ld %d has taken a fork\n", ft_current_pr_time(ph), ph->id);
	pthread_mutex_unlock(ph->entry_point);
	return (0);
}
