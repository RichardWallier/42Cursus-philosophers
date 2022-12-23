/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 03:28:00 by rwallier          #+#    #+#             */
/*   Updated: 2022/12/23 03:28:14 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_die_status(t_args *args)
{
	pthread_mutex_lock(args->die_status_mutex);
	*args->die_status = 1;
	pthread_mutex_unlock(args->die_status_mutex);

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

void	count_eat(t_args *args)
{
	pthread_mutex_lock(args->satiate_mutex);
	args->satiate++;
	pthread_mutex_unlock(args->satiate_mutex);
}

void	set_satiate(t_args *args)
{
	if (args->times_to_eat == 0)
	{
		pthread_mutex_lock(args->satiate_mutex);
		args->satiate[0]++;
		pthread_mutex_unlock(args->satiate_mutex);
	}
}
