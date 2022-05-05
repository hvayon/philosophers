/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:26:54 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/03 18:00:08 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *ph, pthread_t	*th)
{
	int	i;

	i = 0;
	while (ph->in_data->number_of_philosophers > i)
	{
		pthread_mutex_destroy(&ph[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(ph->entry_point);
	pthread_mutex_destroy(ph->finish_mut);
	free(th);
	free(ph->in_data);
	free(ph);
}

t_args	*data_init(int argc, char **argv)
{
	t_args	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_args));
	if (!data)
		return (NULL);
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
	return (data);
}

int	main(int argc, char **argv)
{
	t_args			*data;
	t_philo			*ph;
	pthread_t		*th;
	pthread_mutex_t	entry_point;
	pthread_mutex_t	finish_mut;

	pthread_mutex_init(&entry_point, NULL);
	pthread_mutex_init(&finish_mut, NULL);
	if (argc > 6 || argc < 5)
		return (1);
	data = data_init(argc, argv);
	if (!data)
		return (1);
	ph = ph_init(data, entry_point, finish_mut);
	if (!ph)
		return (1);
	th = make_threads(data, ph);
	if (!th)
		return (1);
	ft_free(ph, th);
	return (0);
}
