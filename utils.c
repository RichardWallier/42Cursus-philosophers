/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:05:08 by rwallier          #+#    #+#             */
/*   Updated: 2022/12/08 14:47:48 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

int	parse_args(t_args *args, const char **argv, int argc)
{
	args->time_to_die = ft_atoi(argv[argc - 3]);
	args->time_to_eat = ft_atoi(argv[argc - 2]);
	printf("%d\n", args->time_to_eat);
	args->time_to_sleep = ft_atoi(argv[argc - 1]);
	return (1);
}

long int	get_actual_ms(void)
{
	struct timeval	current_time;
	long int	ms;

	gettimeofday(&current_time, NULL);
	ms = (current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000;
	return (ms);
}

int	ft_atoi(const char *str)
{
	long int	res;
	int			i;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '+')
	{
		if (sign == -1)
			return (0);
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (sign * res);
}

void	ft_smart_sleep(int milisseconds)
{
	long int	start_ms;

	start_ms = get_actual_ms();
	while (start_ms + milisseconds >= get_actual_ms())
		;
	return ;
}
