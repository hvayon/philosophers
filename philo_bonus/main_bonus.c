/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:41:45 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/08 17:42:06 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_init(t_args *data)
{
	sem_unlink("fork");
	sem_unlink("entry_point");
	data->fork = sem_open("fork", O_CREAT, S_IRWXU, data->number_of_philo);
	data->entry_point = sem_open("entry_point", O_CREAT, S_IRWXU, 1);
}

void	delete_sem(t_args *data)
{
	sem_close(data->entry_point);
	sem_close(data->fork);
	sem_unlink("entry_point");
	sem_unlink("fork");
}

t_args	*data_init(int argc, char **argv)
{
	t_args	*data;

	data = malloc(sizeof(t_args));
	if (!data)
		return (NULL);
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_eat = -1;
	if (argc == 6)
		data->number_of_eat = ft_atoi(argv[5]);
	if (data->number_of_philo < 1 || data->number_of_philo > 200 \
	|| data->time_to_die < 1 || data->time_to_eat < 1 \
	|| data->time_to_sleep < 1 || data->number_of_eat < -1)
		exit (0);
	data->start_eat = ft_current_time();
	return (data);
}

int	main(int argc, char **argv)
{
	t_args			*data;

	if (argc > 6 || argc < 5)
		return (1);
	data = data_init(argc, argv);
	if (!data)
		return (1);
	ft_sem_init(data);
	make_philo(data);
	if (data->counter == data->number_of_philo)
		exit_philo(data);
	else
		philo(data);
	delete_sem(data);
	return (0);
}
