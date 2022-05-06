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

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *)b;
	while (len--)
	{
		*str = (unsigned char)c;
		str++;
	}
	return (b);
}

long	ft_current_time(void)
{
	long		value;
	t_timeval	time;

	gettimeofday(&time, NULL);
	value = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (value);
}

void	ft_usleep(long int time)
{
	long	i;

	i = ft_current_time();
	while ((ft_current_time() - i) < time)
		usleep(100);
}


long	ft_current_pr_time(t_philo *ph)
{
	t_timeval	current_time;
	long		value;

	gettimeofday(&current_time, NULL);
	value = (current_time.tv_sec - ph->program_start_time.tv_sec) * 1000 + \
				(current_time.tv_usec - ph->program_start_time.tv_usec) / 1000;
	return (value);
}

void	*monitor(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	//usleep(100);
	while (1)
	{
		if ((ft_current_time() - ph->start_eat) >= \
									(ph->in_data->time_to_die))
		{
			sem_wait(ph->entry_point);
			printf("%ld %d died\n", ft_current_time() - \
									ph->in_data->start_time, ph->counter);
			exit (0);
		}
	}
}


int	ft_printf(t_philo *ph, int flag)
{
	sem_wait(ph->entry_point);
	if (flag == 1)
		printf("%ld %d is eating\n", ft_current_pr_time(ph), ph->counter);
	if (flag == 2)
		printf("%ld %d is sleeping\n", ft_current_pr_time(ph), ph->counter);
	if (flag == 3)
		printf("%ld %d is thinking\n", ft_current_pr_time(ph), ph->counter);
	if (flag == 4)
		printf("%ld %d has taken a fork\n", ft_current_pr_time(ph), ph->counter);
	sem_post(ph->entry_point);
	return (0);
}

void	make_philo(t_philo *ph) //делаем форки
{
	ph->pids = (int *)malloc(sizeof(int) * ph->in_data->number_of_philo); //почистить их потом
	while(ph->counter < ph->in_data->number_of_philo)
	{
		ph->pids[ph->counter] = fork();
		if (ph->pids[ph->counter] == -1)
			printf("Error create fork");
		if (ph->pids[ph->counter] == 0)
		{
			ph->start_eat = ft_current_time();
			philo(ph);
		}
		ph->counter++;
	}
}

//------start------

void	*philo(t_philo *ph)
{
	pthread_t check_monitor;
	int	ph_ok;

	ph->counter++;
	ph_ok = pthread_create(&check_monitor, NULL, monitor, ph);
	if (ph_ok)
		return (NULL);
	pthread_detach(check_monitor);
	if (ph->counter % 2)
		usleep(2500);
	while(ph->number_of_eat)
	{
		sem_wait(ph->fork);
		ft_printf(ph, FORK);
		sem_wait(ph->fork);
		ft_printf(ph, FORK);
		ph->start_eat = ft_current_time();
		ft_printf(ph, EATING);
		ft_usleep(ph->in_data->time_to_eat);
		sem_post(ph->fork);
		sem_post(ph->fork);
		ft_printf(ph, SLEEPING);
		ft_usleep(ph->in_data->time_to_sleep);
		ft_printf(ph, THINKING);
		if (ph->number_of_eat != -1)
			ph->number_of_eat -= 1;
	}
	exit(1);
}


void	ft_sem_init(t_philo *ph) //инициализация
{
	sem_open("fork", O_CREAT, S_IRWXU, ph->in_data->number_of_philo);
	sem_open("entry_point", O_CREAT, S_IRWXU, 1);
	//data->write = sem_open("write", O_CREAT, S_IRWXU, 1); // ???
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

t_philo	*ph_init(t_args *data)
{
	t_philo			*ph;
	int				i;

	i = 0;
	ph = malloc(sizeof(t_philo));
	if (!ph)
		return (NULL);
	ph->counter = 0;
	ph->number_of_eat = data->number_of_eat;
	ph->in_data = data;
	ph->program_start_time = data->program_start_time;
	ph->finish_act = 0;
	ph->start_eat = ft_current_time();
	gettimeofday(&ph[i].last_eating_time, 0);
	return (ph);
}

void	exit_philo(t_philo *ph)
{
	int status;
	int i;

	i = 0;
	int *y;
	
	y = malloc(sizeof(int) * ph->in_data->number_of_philo);
	ft_memset(y, 0, sizeof(int) * ph->in_data->number_of_philo);
	printf("Y = %d\n", y[0]);
	printf("Y = %d\n", y[1]);
	printf("Y = %d\n", y[2]);
	printf("Y = %d\n", y[3]);
	printf("Y = %d\n", y[4]);
	i = -1;
	while (++i < ph->in_data->number_of_philo)
	{
		waitpid(-1, &status, 0);
		if (!status)
		{
			i = -1;
			while(++i < ph->in_data->number_of_philo)
			{
				printf("Check\n");
				kill(ph->pids[i], SIGTERM);
			}
			break;
		}
		y[i] = 1;
	}
	printf("Y = %d\n", y[0]);
	printf("Y = %d\n", y[1]);
	printf("Y = %d\n", y[2]);
	printf("Y = %d\n", y[3]);
	printf("Y = %d\n", y[4]);
	i = -1;
	while (++i < ph->in_data->number_of_philo)
		if (y[i] == 0)
			break ;
	if (i == ph->in_data->number_of_philo)
		printf("All %d philo has finished\n", ph->counter);
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
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->eat_counter = 0;
	data->counter = 0;
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
	//sem_t			*semaphore;

	if (argc > 6 || argc < 5)
		return (1);
	data = data_init(argc, argv);
	if (!data)
		return (1);
	ph = ph_init(data);
	ft_sem_init(ph); //сделать симафоры
	make_philo(ph);
	exit_philo(ph);
	return (0);
}