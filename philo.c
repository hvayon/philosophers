/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:13 by natalia           #+#    #+#             */
/*   Updated: 2022/04/30 20:55:13 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //delite

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS        0


t_args *data_init(int argc, char **argv)
{
		t_args *data;
		int i;

		i = 0;
		data = malloc(sizeof(t_args)); // нужен ли маллок
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
		if (argc == 6)
			data->number_of_eat = ft_atoi(argv[5]);
		return(data);
}

t_philo *ph_init(t_args *data, pthread_mutex_t	*entry_point)
{
			t_philo *ph;
			int       i;

			i = 0;
			ph = malloc(sizeof(t_philo) * data->number_of_philosophers);
			if (!ph)
					return(NULL);
			// определяем значения для каждого философа
			while(i < data->number_of_philosophers)
			{
				ph[i].id = i + 1; //номер философа
				ph[i].number_of_eat = data->number_of_eat;
				ph[i].in_data = data;
				ph[i].program_start_time = data->program_start_time;
				ph[i].entry_point = entry_point;
				gettimeofday(&ph[i].last_eating_time, 0);
				pthread_mutex_init(&ph[i].right_fork, NULL); //инициализируем все вилки // попробовать сделать указатель
				i++;
			}
			printf("i = %d\n", i);
			//вилки
			i = 1;
			while(i < data->number_of_philosophers)
			{
				ph[i].left_fork = &ph[i - 1].right_fork; //левая вилка - это значение правой -1
				i++;
			}
			ph[0].left_fork = &ph[i - 1].right_fork;
			return(ph);
}

long  ft_current_time(t_philo *ph)
{
		t_timeval current_time;
		long    value;
		gettimeofday(&current_time, NULL);
		value = (current_time.tv_sec - ph->program_start_time.tv_sec) * 1000 + (current_time.tv_usec - ph->program_start_time.tv_usec)  / 1000;
		// printf("seconds : %ld\nmicro seconds : %ld",
		// current_time.tv_sec, current_time.tv_usec);
		return(value);
}

int  is_dead(t_philo *ph)
{
	t_timeval current_time;
	long	value;
	gettimeofday(&current_time, 0); //получаем текущее время // смотрим на время обеда в структуре философ
	if ((current_time.tv_sec - ph->last_eating_time.tv_sec) * 1000 + (current_time.tv_usec - ph->last_eating_time.tv_usec) / 1000 >= ph->in_data->time_to_die)
		return(1);
	return(0);
	// вычетаем разницу
	// переводим в милисекунды
	//если это значение оказалось больше чем time_to_die, то он умер
	
}

void	*ft_philo_was_died(void *ph)
{
	int i;
	i = 0;

	while(1)
	{
		if(is_dead(&ph[i]) == 1)
		{
			printf("Philo %d is dead", i);
			break ;
		}
		i++;
	}
	return(NULL);
}

void  ft_last_eating_time(t_timeval *timeval, t_philo *ph, int was_sleeping)
{
	timeval->tv_usec = ph->in_data->time_to_eat * 1000;
	if (timeval->tv_usec >= 100000)
	{
		timeval->tv_sec++;
		timeval->tv_usec -= 100000;
	}
	if (was_sleeping)
	{
		timeval->tv_usec += ph->in_data->time_to_sleep;
		if (timeval->tv_usec >= 100000)
		{
			timeval->tv_sec++;
			timeval->tv_usec -= 100000;
		}
	}
	
}

//----разбить эту функцию по функциям eat, sleep, think
void *philo(void *philo)
{
	t_philo	*ph;
	int was_sleeping = 0;
	
	pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;
	ph = (t_philo *)philo;
	if (ph->id % 2)
		usleep(2500); // чтобы философы неодновременно подходили к столу
	while(1)
	{
		pthread_mutex_lock(ph->left_fork); 
		pthread_mutex_lock(&entry_point); //добавить глобальный mutex на printf
		printf("%ld %d was taken a fork\n", ft_current_time(ph), ph->id);
		pthread_mutex_unlock(&entry_point);
		pthread_mutex_lock(&ph->right_fork);
		pthread_mutex_lock(&entry_point);
		printf("%ld %d was taken a fork\n",  ft_current_time(ph), ph->id);
		pthread_mutex_unlock(&entry_point);
		pthread_mutex_lock(&entry_point);
		printf("%ld %d is eating\n", ft_current_time(ph), ph->id);
		pthread_mutex_unlock(&entry_point);
		ft_last_eating_time(&ph->last_eating_time, ph, was_sleeping); //время последнего обеда
		usleep(ph->in_data->time_to_eat * 1000);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(&ph->right_fork);
		pthread_mutex_lock(&entry_point);
		printf("%ld %d is sleeping\n", ft_current_time(ph), ph->id);
		pthread_mutex_unlock(&entry_point);
		usleep(ph->in_data->time_to_sleep * 1000);
		pthread_mutex_lock(&entry_point);
		printf("%ld %d is thinking\n", ft_current_time(ph), ph->id);
		pthread_mutex_unlock(&entry_point);
		if (ph->number_of_eat != -1)
			ph->number_of_eat -= 1;
	}
	ph->in_data->eat_counter++;
	ph->finish_act = 1;
	return (NULL);
}

int	analisys(t_philo *ph, int i)
{
	t_timeval current_time;
	while (i < ph->in_data->number_of_philosophers)
	{
		if (ph->in_data->number_of_philosophers == ph->in_data->eat_counter)
		{
			pthread_mutex_lock(ph->entry_point);
			printf("All %d iter has ended\n", ph->in_data->eat_counter);
			return (1);
		}
		if (!ph[i].finish_act)
		{	
			if ((current_time.tv_sec - ph->last_eating_time.tv_sec) * 1000 + (current_time.tv_usec - ph->last_eating_time.tv_usec) / 1000 > ph->in_data->time_to_die) // убрала >=
			{
				pthread_mutex_lock(ph->entry_point);
				printf("%ld %d died\n", (current_time.tv_sec - ph->last_eating_time.tv_sec) * 1000 + (current_time.tv_usec - ph->last_eating_time.tv_usec) / 1000, ph->id);
				return (1);
			}
		}
		usleep(1000);// зачем?
		i++;
	}
	return (0);
}

void	*inspect(void *philo)
{
	int		i;
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		i = 0;
		if (analisys(ph, i))
			break ;
	}
	return (NULL);
}


void *test1(void *ph)
{
	printf("Test1\n");
	return(NULL);	
}

pthread_t  *make_threads(t_args *data, t_philo *ph)
{
		int num;
		int status;
		int i;
		pthread_t	*th;
		pthread_t	monitor;
		int			th_ok;

		pthread_mutex_t mutexs[200];
		
		th = (pthread_t *)malloc(sizeof(pthread_t) * data->number_of_philosophers); // зачем записывать в malloc
		if (!th)
			free(th);
		th_ok = pthread_create(&monitor, NULL, inspect, ph); // что-то не работает
		if (th_ok)
			return(NULL);
		i = 0;
		while (i < data->number_of_philosophers)
		{
			num = pthread_create(&th[i], 0, philo, &(ph[i])); // сохранить номер философа
			if (num)
				return (NULL);
			printf("%d\n", num);
			printf("Hello from main!\n");
			i++;
		}
		pthread_join(monitor, NULL);
		i = 0;
		while(i < data->number_of_philosophers)
		{
			status = pthread_join(th[i], 0);
			if (status != SUCCESS)
					printf("main error: can't join thread, status = %d\n", status);
			i++;
		}
		// join all other threads (philos)
		// clear all resources (memory, mutex...)
		return(th);
}

int main(int argc, char **argv)
{
		t_args  *data;
		t_philo *ph;
		pthread_t *id;
		pthread_mutex_t	*entry_point;

		if (argc > 6 || argc < 5)
		return (1); //написать функцию с ошибками
		else
				printf("All ok\n");
		data = data_init(argc, argv);
		if (!data)
			return(1);
		ph = ph_init(data, entry_point);
		if (!ph)
			return(1);
		make_threads(data, ph);
		//ft_current_time(ph);
		//цикл для создание количества потоков равное количеству философов
		//while(1), в котором проверка на живого философа
		return(0);
}