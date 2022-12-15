/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:16:40 by rwallier          #+#    #+#             */
/*   Updated: 2022/12/15 11:17:15 by rwallier         ###   ########.fr       */
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
		pthread_mutex_lock(&args->checkpoint);
		if (current_time >= args->time_checkpoint + args->time_to_die)
		{
			pthread_mutex_lock(args->print);
			printf("%lli %d died\n", current_time, args->philosopher);
			pthread_mutex_lock(args->die_status_mutex);
			*args->die_status = 1;
			pthread_mutex_unlock(args->die_status_mutex);
			return ((void *)42);
		}
		pthread_mutex_unlock(&args->checkpoint);
	}
	return (NULL);
}

void	set_checkpoint(t_args *args)
{
	pthread_mutex_lock(&args->checkpoint);
	args->time_checkpoint = get_actual_ms();
	pthread_mutex_unlock(&args->checkpoint);
}

void	print_status(t_args *args, char *message)
{
	pthread_mutex_lock(args->print);
	printf("%li %d %s\n", get_actual_ms(), args->philosopher, message);
	pthread_mutex_unlock(args->print);
}

void	eating(void *arg, int left_fork, int right_fork)
{
	t_args			*args;

	args = arg;
	set_checkpoint(args);
	pthread_mutex_lock(&args->mutex[right_fork]);
	print_status(args, "has taken a fork");
	pthread_mutex_lock(&args->mutex[left_fork]);
	print_status(args, "has taken a fork");
	set_checkpoint(args);
	print_status(args, "is eating");
	ft_smart_sleep(args->time_to_eat);
	print_status(args, "is sleeping");
	pthread_mutex_unlock(&args->mutex[right_fork]);
	pthread_mutex_unlock(&args->mutex[left_fork]);
	ft_smart_sleep(args->time_to_sleep);
	print_status(args, "is thinking");
}

void	*routine(void *arg)
{
	t_args			*args;
	pthread_t		thread;

	args = arg;
	pthread_mutex_lock(&args->checkpoint);
	args->time_checkpoint = get_actual_ms();
	if (pthread_mutex_init(&args->checkpoint, NULL) != 0)
		return (NULL);
	pthread_mutex_unlock(&args->checkpoint);
	pthread_create(&thread, NULL, &die_monitoring, args);
	while (42)
	{
		if (args->philosopher == 0)
			eating(arg, args->philosopher, args->amount_of_forks - 1);
		else
			eating(arg, args->philosopher - 1, args->philosopher);
	}
	return (NULL);
}
