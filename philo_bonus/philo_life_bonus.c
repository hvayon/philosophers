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

void	ft_philo_eating(t_args *data)
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
}

void	ft_philo_sleeping(t_args *data)
{
	ft_printf(data, SLEEPING);
	ft_usleep(data->time_to_sleep);
}

void	ft_philo_thinking(t_args *data)
{
	ft_printf(data, THINKING);
}
