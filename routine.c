/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:16:40 by rwallier          #+#    #+#             */
/*   Updated: 2022/10/16 16:58:43 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	has_fork(int left_fork, int right_fork, t_args *args)
{
	if (args->forks[left_fork] == 0)
		return (1);
	if (args->forks[right_fork] == 0)
		return (2);
	return (0);
}

void	*die_monitoring(void *arg)
{
	struct timeval	current_time;
	t_args			*args;

	args = arg;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		if (current_time.tv_usec >= args->time_checkpoint + args->time_to_die)
		{
			gettimeofday(&current_time, NULL);
			printf("%lu %d is died\n", current_time.tv_usec, args->philosopher);
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_args			*args;
	pthread_t		thread;
	struct timeval	current_time;
	int				forks;

	gettimeofday(&current_time, NULL);
	args = arg;
	args->time_checkpoint = 9999999999999999999u;
	forks = 0;
	pthread_create(&thread, NULL, &die_monitoring, args);
	while (1)
	{
		while (1)
		{
			if (args->philosopher == 0)
			{
				if (args->forks[args->philosopher] == 0)
				{
					pthread_mutex_lock(&args->mutex);
					gettimeofday(&current_time, NULL);
					printf("%lu %d has taken a fork\n", current_time.tv_usec, args->philosopher);
					args->forks[args->philosopher] = 1;
					forks++;
					pthread_mutex_unlock(&args->mutex);
				}
				if (args->forks[args->amount_of_forks - 1] == 0)
				{
					pthread_mutex_lock(&args->mutex);
					gettimeofday(&current_time, NULL);
					printf("%lu %d has taken a fork\n", current_time.tv_usec, args->philosopher);
					args->forks[args->amount_of_forks - 1] = 1;
					forks++;
					pthread_mutex_unlock(&args->mutex);
				}
				if (forks == 2)
				{
					gettimeofday(&current_time, NULL);
					args->time_checkpoint = current_time.tv_usec;
					printf("%lu %d is eating\n", current_time.tv_usec, args->philosopher);
					usleep(args->time_to_eat);
					pthread_mutex_lock(&args->mutex);
					args->forks[args->amount_of_forks - 1] = 0;
					args->forks[args->philosopher] = 0;
					pthread_mutex_unlock(&args->mutex);
					forks = 0;
					printf("%lu %d is sleeping\n", current_time.tv_usec, args->philosopher);
					usleep(args->time_to_sleep);
					break;
				}
			}
			else
			{
				if (has_fork(args->philosopher - 1, args->philosopher, args) == 2)
				{
					gettimeofday(&current_time, NULL);
					printf("%lu %d has taken a fork\n", current_time.tv_usec, args->philosopher);
					pthread_mutex_lock(&args->mutex);
					args->forks[args->philosopher] = 1;
					forks++;
					pthread_mutex_unlock(&args->mutex);
				}
				if (has_fork(args->philosopher - 1, args->philosopher, args) == 1)
				{
					gettimeofday(&current_time, NULL);
					printf("%lu %d has taken a fork\n", current_time.tv_usec, args->philosopher);
					pthread_mutex_lock(&args->mutex);
					args->forks[args->philosopher - 1] = 1;
					forks++;
					pthread_mutex_unlock(&args->mutex);
				}
				if (forks == 2)
				{
					gettimeofday(&current_time, NULL);
					args->time_checkpoint = current_time.tv_usec;
					printf("%lu %d is eating\n", current_time.tv_usec, args->philosopher);
					usleep(args->time_to_eat);
					pthread_mutex_lock(&args->mutex);
					args->forks[args->philosopher - 1] = 0;
					args->forks[args->philosopher] = 0;
					pthread_mutex_unlock(&args->mutex);
					forks = 0;
					gettimeofday(&current_time, NULL);
					printf("%lu %d is sleeping\n", current_time.tv_usec, args->philosopher);
					usleep(args->time_to_sleep);
					break;
				}
			}
		}
		gettimeofday(&current_time, NULL);
		printf("%lu %d is thinking\n", current_time.tv_usec, args->philosopher);
	}
	return (NULL);
}

