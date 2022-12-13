/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:22:44 by rwallier          #+#    #+#             */ /*   Updated: 2022/12/08 16:10:29 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_args
{
	int				amount_of_forks;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				*forks;
	int				philosopher;
	long int	time_checkpoint;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	checkpoint;
}				t_args;

void		*routine(void *arg);

int			create_threads(pthread_t **thread, t_args *args, int philo_amount);

int			create_mutex(t_args *args, int amount_of_forks);

int			parse_args(t_args *args, const char **argv, int argc);

int			wait_threads(pthread_t **thread, int threads_amount);

int			ft_atoi(const char *str);

long int	get_actual_ms(void);

int			free_all(t_args *args, pthread_t **threads);

void	ft_smart_sleep(int milisseconds);

#endif // !PHILOSOPHERS_H
