/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:16:40 by rwallier          #+#    #+#             */
/*   Updated: 2022/10/17 10:38:48 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*die_monitoring(void *arg)
{
	// struct timeval	current_time;
	t_args			*args;

	args = arg;
	// while (1)
	// {
	// 	gettimeofday(&current_time, NULL);
	// 	if (current_time.tv_usec >= (args->time_checkpoint + args->time_to_die))
	// 	{
	// 		gettimeofday(&current_time, NULL);
	// 		printf("%d %d is died\n", current_time.tv_usec, args->philosopher);
	// 		free(args);
	// 		exit(EXIT_SUCCESS);
	// 	}
	// }
	usleep(5 * 1000000);
	free(args);
	exit(0);
	return (NULL);
}

void	*routine(void *arg)
{
	t_args			*args;
	pthread_t		thread;
	struct timeval	current_time;
	int				forks;

	args = arg;
	gettimeofday(&current_time, NULL);
	args->time_checkpoint = current_time.tv_usec;
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
					gettimeofday(&current_time, NULL);
					printf("%d %d has taken a fork\n", current_time.tv_usec, args->philosopher);
					pthread_mutex_lock(&args->mutex[args->philosopher]);
					args->forks[args->philosopher] = 1;
					pthread_mutex_unlock(&args->mutex[args->philosopher]);
					forks++;
				}
				if (args->forks[args->amount_of_forks - 1] == 0)
				{
					gettimeofday(&current_time, NULL);
					printf("%d %d has taken a fork\n", current_time.tv_usec, args->philosopher);
					pthread_mutex_lock(&args->mutex[args->amount_of_forks - 1]);
					args->forks[args->amount_of_forks - 1] = 1;
					pthread_mutex_unlock(&args->mutex[args->amount_of_forks - 1]);
					forks++;
				}
				if (forks == 2)
				{
					gettimeofday(&current_time, NULL);
					args->time_checkpoint = current_time.tv_usec;
					printf("%d %d is eating\n", current_time.tv_usec, args->philosopher);
					usleep(args->time_to_eat);
					pthread_mutex_lock(&args->mutex[args->amount_of_forks - 1]);
					pthread_mutex_lock(&args->mutex[args->philosopher]);
					args->forks[args->amount_of_forks - 1] = 0;
					args->forks[args->philosopher] = 0;
					pthread_mutex_unlock(&args->mutex[args->amount_of_forks - 1]);
					pthread_mutex_unlock(&args->mutex[args->philosopher]);
					forks = 0;
					printf("%d %d is sleeping\n", current_time.tv_usec, args->philosopher);
					usleep(args->time_to_sleep);
					break;
				}
			}
			else
			{
				if (args->forks[args->philosopher] == 0)
				{
					gettimeofday(&current_time, NULL);
					printf("%d %d has taken a fork\n", current_time.tv_usec, args->philosopher);
					pthread_mutex_lock(&args->mutex[args->philosopher]);
					args->forks[args->philosopher] = 1;
					pthread_mutex_unlock(&args->mutex[args->philosopher]);
					forks++;
				}
				if (args->forks[args->philosopher - 1] == 0)
				{
					gettimeofday(&current_time, NULL);
					printf("%d %d has taken a fork\n", current_time.tv_usec, args->philosopher);
					pthread_mutex_lock(&args->mutex[args->philosopher - 1]);
					args->forks[args->philosopher - 1] = 1;
					pthread_mutex_unlock(&args->mutex[args->philosopher - 1]);
					forks++;
				}
				if (forks == 2)
				{
					gettimeofday(&current_time, NULL);
					args->time_checkpoint = current_time.tv_usec;
					printf("%d %d is eating\n", current_time.tv_usec, args->philosopher);
					usleep(args->time_to_eat);
					pthread_mutex_lock(&args->mutex[args->philosopher - 1]);
					pthread_mutex_lock(&args->mutex[args->philosopher]);
					args->forks[args->philosopher - 1] = 0;
					args->forks[args->philosopher] = 0;
					pthread_mutex_unlock(&args->mutex[args->philosopher - 1]);
					pthread_mutex_unlock(&args->mutex[args->philosopher]);
					forks = 0;
					printf("%d %d is sleeping\n", current_time.tv_usec, args->philosopher);
					usleep(args->time_to_sleep);
					break;
				}
			}
		}
		gettimeofday(&current_time, NULL);
		printf("%d %d is thinking\n", current_time.tv_usec, args->philosopher);
	}
	return (NULL);
}

