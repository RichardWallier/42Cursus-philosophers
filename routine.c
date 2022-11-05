/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:16:40 by rwallier          #+#    #+#             */
/*   Updated: 2022/11/04 22:31:36 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*die_monitoring(void *arg)
{
	t_args			*args;
	long long int	current_time;

	args = arg;
	while (1)
	{
		current_time = get_actual_ms();
		if (current_time >= args->time_checkpoint + args->time_to_die)
		{
			printf("%lli %d died\n", current_time, args->philosopher);
			exit(1);
		}
	}
	return (NULL);
}

void	eating(void *arg, int left_fork, int right_fork)
{
	t_args			*args;
	long long int	current_time;

	args = arg;
	args->time_checkpoint = get_actual_ms();
	pthread_mutex_lock(&args->mutex[right_fork]);
	current_time = get_actual_ms();
	printf("%lli %d has taken a right fork\n", current_time, args->philosopher);
	pthread_mutex_lock(&args->mutex[left_fork]);
	current_time = get_actual_ms();
	printf("%lli %d has taken a left fork\n", current_time, args->philosopher);
	current_time = get_actual_ms();
	printf("%lli %d is eating\n", current_time, args->philosopher);
	args->time_checkpoint = current_time;
	usleep(args->time_to_eat * 1000);
	pthread_mutex_unlock(&args->mutex[right_fork]);
	pthread_mutex_unlock(&args->mutex[left_fork]);
	current_time = get_actual_ms();
	printf("%lli %d is sleeping\n", current_time, args->philosopher);
	usleep(args->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_args			*args;
	pthread_t		thread;
	long long int	current_time;

	args = arg;
	args->time_checkpoint = get_actual_ms();
	pthread_create(&thread, NULL, &die_monitoring, args);
	while (42)
	{
		if (args->philosopher == 0)
			eating(arg, args->amount_of_forks - 1, args->philosopher);
		else
			eating(arg, args->philosopher - 1, args->philosopher);
		current_time = get_actual_ms();
		printf("%lli %d is thinking\n", current_time, args->philosopher);
	}
	return (NULL);
}
