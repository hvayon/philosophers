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

int	ft_no_finish_act(t_philo *ph, int i)
{
	if (!ph[i].finish_act)
	{	
		pthread_mutex_lock(ph->entry_point);
		if ((ft_current_time() - ph[i].start_eat) >= \
									(ph->in_data->time_to_die))
		{
			pthread_mutex_unlock(ph->finish_mut);
			pthread_mutex_unlock(ph->entry_point);
			pthread_mutex_lock(ph->entry_point);
			printf("%ld %d died\n", ft_current_time() - \
								ph->in_data->start_time, ph->id);
			return (1);
		}
		pthread_mutex_unlock(ph->entry_point);
	}
	return (0);
}

int	is_dead(t_philo *ph, int i)
{
	while (i < ph->in_data->number_of_philo)
	{
		pthread_mutex_lock(ph->finish_mut);
		if (ph->in_data->number_of_philo == ph->in_data->eat_counter)
		{
			pthread_mutex_unlock(ph->finish_mut);
			pthread_mutex_lock(ph->entry_point);
			printf("All the philosophers has eaten %d times each\n", \
										ph->in_data->number_of_eat);
			return (1);
		}
		pthread_mutex_unlock(ph->finish_mut);
		pthread_mutex_lock(ph->finish_mut);
		if (ft_no_finish_act(ph, i) == 1)
			return (1);
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
	usleep(900);
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
	int			i;
	pthread_t	*th;
	int			th_ok;

	th = (pthread_t *)malloc(sizeof(pthread_t) * \
				(data->number_of_philo + 1));
	if (!th)
		return (NULL);
	data->start_time = ft_current_time();
	i = -1;
	while (++i < data->number_of_philo)
	{
		th_ok = pthread_create(&th[i], 0, philo, &(ph[i]));
		if (th_ok)
			return (NULL);
		pthread_detach(th[i]);
	}
	monitor(ph);
	return (th);
}
