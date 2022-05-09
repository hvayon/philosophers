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

void	make_philo(t_args *data)
{
	data->counter = 0;
	while (data->counter < data->number_of_philo)
	{
		data->pids[data->counter] = fork();
		if (data->pids[data->counter] == -1)
		{
			printf("Error create fork");
			break ;
		}
		if (data->pids[data->counter] == 0)
			break ;
		data->counter++;
	}
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
		printf("All the philosophers has eaten %d\n", data->number_of_eat);
}
