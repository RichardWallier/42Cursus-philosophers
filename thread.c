/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 08:37:54 by rwallier          #+#    #+#             */
/*   Updated: 2022/12/08 16:17:47 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutex(t_args *args, int amount_of_forks)
{
	int		index;

	args->mutex = malloc(amount_of_forks * sizeof(pthread_mutex_t));
	index = 0;
	while (index < amount_of_forks)
	{
		if (pthread_mutex_init(&(args->mutex)[index], NULL) != 0)
			return (1);
		index++;
	}
	if (pthread_mutex_init(&args->checkpoint, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&args->print, NULL) != 0)
		return (1);
	return (0);
}

int	create_threads(pthread_t **thread, t_args *args, int philo_amount)
{
	int		index;
	t_args	*current_arg;

	*thread = malloc(philo_amount * sizeof(pthread_t));
	index = 0;
	while (index < philo_amount)
	{
		current_arg = malloc(1 * sizeof(t_args));
		current_arg->forks = args->forks;
		current_arg->mutex = args->mutex;
		current_arg->print = args->print;
		current_arg->checkpoint = args->checkpoint;
		current_arg->philosopher = index;
		current_arg->amount_of_forks = philo_amount;
		current_arg->time_to_die = args->time_to_die;
		current_arg->time_to_eat = args->time_to_eat;
		current_arg->time_to_sleep = args->time_to_sleep;
		if (pthread_create(&(*thread)[index], NULL, &routine, current_arg) != 0)
			return (1);
		index++;
	}
	return (0);
}

int	wait_threads(pthread_t **thread, int threads_amount)
{
	int		index;

	index = 0;
	while (index < threads_amount)
	{
		if (pthread_join((*thread)[index], NULL) != 0)
			return (1);
		index++;
	}
	return (0);
}
