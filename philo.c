/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:13 by natalia           #+#    #+#             */
/*   Updated: 2022/04/29 21:41:43 by natalia          ###   ########.fr       */
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
    gettimeofday(&data->program_start_time, 0);
    if (argc == 6)
	    data->number_of_eat = ft_atoi(argv[5]);
    return(data);
}

t_philo *ph_init(t_args *data)
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
        ph[i].num = i + 1; //номер философа
        ph[i].number_of_eat = data->number_of_eat;
        ph[i].in_data = data;
        ph[i].program_start_time = data->program_start_time;
        pthread_mutex_init(&ph[i].right_fork, NULL);
        i++;
      }
      printf("i = %d\n", i);
      //вилки
      i = 1;
      while(i < data->number_of_philosophers)
      {
        //philo[i + 1].right_fork = philo[i].left_fork; //попробовать поменять потом
        ph[i].left_fork = ph[i - 1].right_fork;
        i++;
      }
      ph[0].right_fork = ph[i - 1].left_fork;
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

//----разбить эту функцию по функциям eat, sleep, think
void *philo(void *philo)
{
  t_philo	*ph;
  
  ph = (t_philo *)philo;
  while(1)
  {
    pthread_mutex_lock(&ph->left_fork);
    //добавить глобальный mutex
    printf("%ld %d was taken a fork\n", ft_current_time(ph), ph->num);
    pthread_mutex_lock(&ph->right_fork);
    printf("%ld %d was taken a fork\n",  ft_current_time(ph), ph->num);
    printf("%ld %d is eating\n", ft_current_time(ph), ph->num);
    usleep(ph->in_data->time_to_eat * 1000);
    pthread_mutex_unlock(&ph->left_fork);
    pthread_mutex_unlock(&ph->right_fork);
    printf("%ld %d is sleeping\n", ft_current_time(ph), ph->num);
    usleep(ph->in_data->time_to_sleep * 1000);
    printf("%ld %d is thinking\n", ft_current_time(ph), ph->num);
  }
}


int  make_threads(t_args *data, t_philo *ph)
{
    int num;
    int status;
    int i;
    pthread_t *id;

    id = malloc(sizeof(pthread_t) * data->number_of_philosophers);
    if (!id)
      free(id);
    printf("Number of philo = %d\n", data->number_of_philosophers);
    i = 0;
    while (i < data->number_of_philosophers)
    {
      num = pthread_create(&id[i], 0, philo, &(ph[i])); // сохранить номер философа
      if (num)
        return (1);
      printf("%d\n", num);
      printf("Hello from main!\n");
    //  pthread_detach(id[i]);
      i++;
    }
    i = 0;
    while(i < data->number_of_philosophers)
    {
      status = pthread_join(id[i], 0);
      if (status != SUCCESS)
          printf("main error: can't join thread, status = %d\n", status);
      i++;
    }
    return(0);
}

int main(int argc, char **argv)
{
    t_args  *data;
    t_philo *ph;
    pthread_t *id;

    if (argc > 6 || argc < 5)
		return (1); //написать функцию с ошибками
    else
        printf("All ok\n");
    data = data_init(argc, argv);
    if (!data)
      return(1);
    ph = ph_init(data);
    if (!ph)
      return(1);
    ph_init(data);
    make_threads(data, ph);
    //ft_current_time(ph);
    //цикл для создание количества потоков равное количеству философов
    //while(1), в котором проверка на живого философа
    return(0);
}