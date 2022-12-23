/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:22:38 by rwallier          #+#    #+#             */
/*   Updated: 2022/12/23 03:13:59 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(const int argc, const char **argv)
{
	t_manage		manage;

	if (argc != 5 && argc != 6)
		return (printf("Wrong arguments!\n"));
	parse_args(&manage, argv, argc);
	if (create_mutex(&manage, ft_atoi(argv[1])) != 0)
	{
		free_all(&manage, &manage.threads);
		return (printf("Error creating mutexes!\n"));
	}
	if (create_threads(&manage, &manage.threads, ft_atoi(argv[1])) != 0)
	{
		free_all(&manage, &manage.threads);
		return (printf("Error creating threads!\n"));
	}
	if (wait_threads(&manage, &manage.threads, ft_atoi(argv[1])) != 0)
	{
		free_all(&manage, &manage.threads);
		return (printf("Error waiting threads\n"));
	}
	free_all(&manage, &manage.threads);
	return (0);
}

int	free_all(t_manage *args, pthread_t **threads)
{
	int	index;

	index = 0;
	if (args->args.mutex)
		free(args->args.mutex);
	if (*threads)
		free(*threads);
	return (1);
}
