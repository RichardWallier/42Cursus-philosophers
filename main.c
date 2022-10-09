/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:22:38 by rwallier          #+#    #+#             */
/*   Updated: 2022/10/09 11:55:52 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <sys/time.h>

void	*routine(void *arg)
{
	t_args *args;
	struct timeval current_time;
	int forks;

	args = arg;
	while (1)
	{
		while (1)
		{
			if (args->forks[args->philosopher] == 0 || args->forks[args->philosopher - 1] == 0)
			{
				pthread_mutex_lock(&args->mutex);
				if (args->forks[args->philosopher] == 0)
				{
					gettimeofday(&current_time, NULL);
					args->forks[args->philosopher] = 1;
					forks++;
					printf("%li philosopher: %d has taken a fork\n", current_time.tv_usec, args->philosopher);
				}
				if (args->forks[args->amount_of_forks - 1])
				{
					gettimeofday(&current_time, NULL);
					args->forks[args->amount_of_forks - 1] = 1;
					forks++;
					printf("%li philosopher: %d has taken a fork\n", current_time.tv_usec, args->philosopher);
				}
				pthread_mutex_unlock(&args->mutex);
				if (forks == 2)
				{
					printf("philosopher: %d eat\n", args->philosopher);
					usleep(args->time_to_eat * 6000000);
					pthread_mutex_lock(&args->mutex);
					args->forks[args->philosopher] = 0;
					args->forks[args->amount_of_forks - 1] = 0;
					pthread_mutex_unlock(&args->mutex);
					forks = 0;
					break;
				}
			}
		}
		printf("philosopher: %d sleep\n", args->philosopher);
		usleep(args->time_to_sleep * 600000);
		printf("philosopher: %d think\n", args->philosopher);
	}
	return (NULL);
}

int		create_threads(pthread_t **thread, t_args *args, int philosophers_amount)
{
	int		index;
	int		*aux;
	t_args	*current_arg;

	*thread = malloc(philosophers_amount * sizeof(pthread_t));
	index = 0;
	while (index < philosophers_amount)
	{
		current_arg = malloc(1 * sizeof(t_args));
		current_arg->forks = args->forks;
		current_arg->mutex = args->mutex;
		current_arg->philosopher = index;
		current_arg->amount_of_forks = philosophers_amount;
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

int	parse_args(t_args *args, const char **argv, int argc)
{
	int	index;

	pthread_mutex_init(&(args->mutex), NULL);
	args->time_to_die = argc - 3;
	args->time_to_eat = argc - 2;
	args->time_to_sleep = argc - 1;
	args->forks = malloc(ft_atoi(argv[argc - 4]) * sizeof(int));
	index = 0;
	while (index < ft_atoi(argv[argc - 4]))
	{
		args->forks[index] = 0;
		index++;
	}
	return (1);
}

int	main(const int argc, const char **argv)
{
	pthread_t	*threads;
	t_args		args;

	if (argc != 5 && argc != 6)
		return (printf("Wrong arguments!\n"));
	parse_args(&args, argv, argc);
	if (create_threads(&threads, &args, ft_atoi(argv[argc - 4])) != 0)
		return (printf("Wrong creating threads!\n"));
	if (wait_threads(&threads, ft_atoi(argv[argc - 4])) != 0)
		return (printf("Error monitoring threads\n"));
	pthread_mutex_destroy(&args.mutex);
	free(args.forks);
	free(threads);
	return (0);
}
