/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:56:22 by rwallier          #+#    #+#             */
/*   Updated: 2022/12/23 03:31:59 by rwallier         ###   ########.fr       */
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
	int				times_to_eat;
	int				philosopher;
	int				*die_status;
	int				*satiate;
	long int		time_checkpoint;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	pthread_mutex_t	*die_status_mutex;
	pthread_mutex_t	*satiate_mutex;
	pthread_mutex_t	checkpoint;
}				t_args;

typedef struct s_manage
{
	t_args		args;
	pthread_t	*threads;
	int			*die_status;
	int			*satiate;
}				t_manage;

void		*routine(void *arg);

int			create_threads( t_manage *args, pthread_t **thread, int philo);

int			create_mutex(t_manage *args, int amount_of_forks);

int			parse_args(t_manage *args, const char **argv, int argc);

int			wait_threads(t_manage *args, pthread_t **thread, int threads);

int			ft_atoi(const char *str);

long int	get_actual_ms(void);

int			free_all(t_manage *args, pthread_t **threads);

void		ft_smart_sleep(int milisseconds);

void		set_die_status(t_args *args);

void		set_checkpoint(t_args *args);

void		print_status(t_args *args, char *message);

void		count_eat(t_args *args);

void		set_satiate(t_args *args);

#endif // !PHILOSOPHERS_H
