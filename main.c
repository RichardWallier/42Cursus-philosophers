/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:22:38 by rwallier          #+#    #+#             */
/*   Updated: 2022/11/04 22:25:19 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(const int argc, const char **argv)
{
	pthread_t	*threads;
	t_args		args;

	if (argc != 5 && argc != 6)
		return (printf("Wrong arguments!\n"));
	parse_args(&args, argv, argc);
	if (create_mutex(&args, ft_atoi(argv[argc - 4])) != 0)
	{
		free_all(&args, &threads);
		return (printf("Error creating mutexes!\n"));
	}
	if (create_threads(&threads, &args, ft_atoi(argv[argc - 4])) != 0)
	{
		free_all(&args, &threads);
		return (printf("Error creating threads!\n"));
	}
	if (wait_threads(&threads, ft_atoi(argv[argc - 4])) != 0)
	{
		free_all(&args, &threads);
		return (printf("Error waiting threads\n"));
	}
	free_all(&args, &threads);
	return (0);
}

int	free_all(t_args *args, pthread_t **threads)
{
	int	index;

	index = 0;
	while (index < args->amount_of_forks)
	{
		pthread_mutex_destroy(&args->mutex[index]);
		index++;
	}
	if (args->mutex)
		free(args->mutex);
	if (*threads)
		free(*threads);
	return (1);
}
