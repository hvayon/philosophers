/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:19:01 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/02 17:23:49 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (str[i] >= 'A' && str[i] <= 'z')
		return (0);
	return (ft_handle_range(res, nominate));
}

void	ft_usleep(long int time)
{
	long	i;

	i = ft_current_time();
	while ((ft_current_time() - i) < time)
		usleep(100);
}

long	ft_current_time(void)
{
	long		value;
	t_timeval	time;

	gettimeofday(&time, NULL);
	value = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (value);
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
