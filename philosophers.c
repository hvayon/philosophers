/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 21:55:04 by natalia           #+#    #+#             */
/*   Updated: 2022/04/20 21:44:30 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h> 

typedef pthread_mutex_t t_mutex;

#include <stdio.h>
#include <unistd.h>

// void *test1(void *data)
// {
//     printf("Hello world\n");
//     return(0);
// }

// void *test2(void *data)
// {
//     int *num = data;
//     while(*num < 100000)
//      (*num)++;
//     return(0);
// }

struct t_data
{
    t_mutex *p_mutex;
    int *num;
};

void *ft_run(void *data)
{
    struct t_data *_data = data;
    pthread_mutex_lock(_data->p_mutex);
    while((*_data->num) < 10)
    {
        (*_data->num)++;
        printf("%d\n", (*_data->num));
        pthread_mutex_unlock(_data->p_mutex);
        pthread_mutex_lock(_data->p_mutex);
    }
    pthread_mutex_unlock(_data->p_mutex);
    return(0);
}

int main()
{
    int tmp = 0;
    pthread_t id;
    t_mutex mutex;
    struct t_data data;
    data.p_mutex = &mutex;
    data.num = &tmp;
    pthread_mutex_init(&mutex, 0);
    pthread_create(&id, 0, ft_run, &data);
    pthread_mutex_lock(&mutex);
    while (tmp <= 10)
    {
        printf("%d\n", tmp);
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&mutex);
    return(0);
}