/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 08:37:54 by rwallier          #+#    #+#             */
/*   Updated: 2022/12/15 10:45:05 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutex(t_manageThreads *args, int amount_of_forks)
{
	int		index;

	args->args.mutex = (pthread_mutex_t *)malloc(amount_of_forks * sizeof(pthread_mutex_t));
	args->args.print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	args->args.die_status_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	index = 0;
	while (index < amount_of_forks)
	{
		if (pthread_mutex_init(&(args->args.mutex)[index], NULL) != 0)
			return (1);
		index++;
	}
	if (pthread_mutex_init(args->args.print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(args->args.die_status_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	create_threads(t_manageThreads *args, pthread_t **thread, int philo_amount)
{
	int		index;
	t_args	*current_arg;

	*thread = malloc(philo_amount * sizeof(pthread_t));
	index = 0;
	while (index < philo_amount)
	{
		current_arg = malloc(1 * sizeof(t_args));
		current_arg->mutex = args->args.mutex;
		current_arg->print = args->args.print;
		current_arg->die_status_mutex = args->args.die_status_mutex;
		current_arg->philosopher = index;
		current_arg->amount_of_forks = philo_amount;
		current_arg->die_status = args->die_status;
		current_arg->time_to_die = args->args.time_to_die;
		current_arg->time_to_eat = args->args.time_to_eat;
		current_arg->time_to_sleep = args->args.time_to_sleep;
		if (pthread_create(&(*thread)[index], NULL, &routine, current_arg) != 0)
			return (1);
		index++;
	}
	return (0);
}

int	wait_threads(t_manageThreads *args, pthread_t **thread, int threads_amount)
{
	int		index;

	index = 0;
	while (42)
	{
		pthread_mutex_lock(args->args.die_status_mutex);
		if (*(args->die_status))
			break;
		pthread_mutex_unlock(args->args.die_status_mutex);
	}
	while (index < threads_amount)
	{
		if (pthread_detach((*thread)[index]) != 0)
			return (1);
		index++;
	}
	return (0);
}
