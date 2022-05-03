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

//void	make_philo
// void	make_fork(t_args *data)
// {
// 	pid_t pid;
// 	int i;
// 	i = 0;
// 	while(i < data->number_of_philosophers)
// 	{
// 		philo->pid[i] = fork();
// 		if (pid == 0)
// 	}
// }

void	ft_sem_init(t_args *data)
{
	sem_open(O_CREAT, data->number_of_philosophers);
}

int	ft_handle_range(long res, int nominate)
{
	if (res >= -2147483648 && res <= 2147483647)
		return ((int)res);
	else if (nominate == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		nominate;
	long	res;

	nominate = 1;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i = i + 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			nominate = nominate * -1;
		i = i + 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = 10 * res + nominate * (str[i] - '0');
		i++;
	}
	return (ft_handle_range(res, nominate));
}

t_args	*data_init(int argc, char **argv)
{
	t_args	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_args));
	if (!data)
		return(NULL);
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
	//pthread_t		*th;
	sem_t			*semaphore;

	if (argc > 6 || argc < 5)
		return (1);
	data = data_init(argc, argv);
	if (!data)
		return (1);
	ft_sem_init(data); //сделать симафоры
	make_philo(); //сделать философов
	return (0);
}