/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:43:06 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/03 14:08:26 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philo_eat(t_philo *ph)
{
	pthread_mutex_unlock(ph->finish_mut);
	pthread_mutex_lock(ph->entry_point);
	printf("All the philosopher has eaten at least %d times each\n", \
										ph->in_data->number_of_eat);
	return (1);
}

int	philo_is_dead(t_philo *ph)
{
	pthread_mutex_unlock(ph->finish_mut);
	pthread_mutex_unlock(ph->entry_point);
	pthread_mutex_lock(ph->entry_point);
	printf("%ld %d died\n", ft_current_time() - \
								ph->in_data->start_time, ph->id);
	return (1);
}

int	is_dead(t_philo *ph, int i)
{
	while (i < ph->in_data->number_of_philosophers)
	{
		pthread_mutex_lock(ph->finish_mut);
		if (ph->in_data->number_of_philosophers == ph->in_data->eat_counter)
			all_philo_eat(ph);
		pthread_mutex_unlock(ph->finish_mut);
		pthread_mutex_lock(ph->finish_mut);
		if (!ph[i].finish_act)
		{	
			pthread_mutex_lock(ph->entry_point);
			if ((ft_current_time() - ph[i].start_eat) >= \
												(ph->in_data->time_to_die))
				philo_is_dead(ph);
			pthread_mutex_unlock(ph->entry_point);
		}
		pthread_mutex_unlock(ph->finish_mut);
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

pthread_t	*make_threads(t_args *data, t_philo *ph)
{
	int			status;
	int			i;
	pthread_t	*th;
	int			th_ok;

	th = (pthread_t *)malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!th)
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		th_ok = pthread_create(&th[i], 0, philo, &(ph[i]));
		if (th_ok)
			return (NULL);
		i++;
	}
	monitor(ph);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		status = pthread_join(th[i], 0);
		if (status != SUCCESS)
			printf("main error: can't join thread, status = %d\n", status);
	}
	return (th);
}
