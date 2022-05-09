/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:18:50 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/03 14:14:04 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_forks(t_args *data, t_philo *ph)
{
	int	i;

	i = 1;
	while (i < data->number_of_philo)
	{
		ph[i].left_fork = &ph[i - 1].right_fork;
		i++;
	}
}

t_philo	*ph_init(t_args *data, pthread_mutex_t entry_point, \
								pthread_mutex_t finish_mut)
{
	t_philo			*ph;
	int				i;

	i = 0;
	ph = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!ph)
		return (NULL);
	while (i < data->number_of_philo)
	{
		ph[i].id = i + 1;
		ph[i].number_of_eat = data->number_of_eat;
		ph[i].in_data = data;
		ph[i].program_start_time = data->program_start_time;
		ph[i].entry_point = &entry_point;
		ph[i].finish_act = 0;
		ph[i].finish_mut = &finish_mut;
		ph[i].start_eat = ft_current_time();
		gettimeofday(&ph[i].last_eating_time, 0);
		pthread_mutex_init(&ph[i].right_fork, NULL);
		i++;
	}
	make_forks(data, ph);
	ph[0].left_fork = &ph[i - 1].right_fork;
	return (ph);
}
