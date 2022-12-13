/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:16:40 by rwallier          #+#    #+#             */
/*   Updated: 2022/12/08 16:54:41 by rwallier         ###   ########.fr       */
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
			printf("%lli %d died\n", current_time, args->philosopher);
			pthread_mutex_unlock(&args->checkpoint);
			return((void *)42);
		}
		pthread_mutex_unlock(&args->checkpoint);
	}
	return (NULL);
}

void	eating(void *arg, int left_fork, int right_fork)
{
	t_args			*args;

	args = arg;
	while (42)
	{
		args->time_checkpoint = get_actual_ms();
		pthread_mutex_lock(&args->mutex[right_fork]);
		pthread_mutex_lock(&args->print);
		printf("%li %d has taken a right fork\n", get_actual_ms(), args->philosopher);
		pthread_mutex_unlock(&args->print);

		pthread_mutex_lock(&args->mutex[left_fork]);
		pthread_mutex_lock(&args->print);
		printf("%li %d has taken a left fork\n", get_actual_ms(), args->philosopher);
		pthread_mutex_unlock(&args->print);

		pthread_mutex_lock(&args->checkpoint);
		args->time_checkpoint = get_actual_ms();
		pthread_mutex_unlock(&args->checkpoint);

		pthread_mutex_lock(&args->print);
		printf("%li %d is eating\n", get_actual_ms(), args->philosopher);
		pthread_mutex_unlock(&args->print);

		ft_smart_sleep(args->time_to_eat);

		pthread_mutex_lock(&args->print);
		printf("%li %d is sleeping\n", get_actual_ms(), args->philosopher);
		pthread_mutex_unlock(&args->print);

		pthread_mutex_unlock(&args->mutex[right_fork]);
		pthread_mutex_unlock(&args->mutex[left_fork]);

		ft_smart_sleep(args->time_to_sleep);

		pthread_mutex_lock(&args->print);
		printf("%li %d is thinking\n", get_actual_ms(), args->philosopher);
		pthread_mutex_unlock(&args->print);
	}
}

void	*routine(void *arg)
{
	t_args			*args;
	pthread_t		thread;
	int			*die_status;

	args = arg;
	if (args->philosopher % 2 == 0)
		usleep(50);
	args->time_checkpoint = get_actual_ms();
	die_status = NULL;
	pthread_create(&thread, NULL, &die_monitoring, args);
		if (args->philosopher == 0)
			eating(arg, args->amount_of_forks - 1, args->philosopher);
		else
			eating(arg, args->philosopher - 1, args->philosopher);
	pthread_join(thread, (void*)&die_status);
	printf("DIEDIEDJIEJHDIUJEIUDJDJAOIHJDIOUwHjnd\n");
	return (NULL);
}
