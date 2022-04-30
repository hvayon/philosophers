/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:44:37 by natalia           #+#    #+#             */
/*   Updated: 2022/04/30 20:43:46 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include <stdio.h>

typedef struct timeval	t_timeval;

typedef struct s_args
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_of_eat;
    int             eat_counter;
    t_timeval       program_start_time;
    pthread_mutex_t write;
}               t_args;

typedef struct s_philo
{
    t_args      *in_data;
    pthread_mutex_t *left_fork; //*
    pthread_mutex_t right_fork; //*
    int             id;
    int             number_of_eat;
    t_timeval       program_start_time;
    t_timeval       last_eating_time;
    int             finish_act;
    pthread_mutex_t	*entry_point;
    
}               t_philo;

int	ft_atoi(const char *str);

# endif
